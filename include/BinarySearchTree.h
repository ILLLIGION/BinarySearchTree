#include <iostream>
#include <fstream>
#include <memory>
#include <exception>

struct l_error : public std::logic_error
{
public:
	l_error(const std::string& data) : logic_error(data) {}
};

template <typename T>
class BinarySearchTree
{
public:
	struct Node
	{
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		T value;

		Node(T value_) : value(value_), left_(nullptr), right_(nullptr) {}

		auto _value() const noexcept -> T { return value; }

		auto equal(std::shared_ptr<Node> tree) const noexcept -> bool
		{
			if ((left_ && !tree->left_) || (right_ && !tree->right_))
				return false;
			if ((!left_ && tree->left_) || (!right_ && tree->right_))
				return false;

			bool equalLeft = true; bool equalRight = true;
			if (value != tree->value)
				return false;
			else
			{
				if (!left_ && !right_)
					return true;
				if (left_)
					equalLeft = left_->equal(tree->left_);
				if (right_)
					equalRight = right_->equal(tree->right_);
				return equalLeft && equalRight;
			}
		}

		static auto remove_node(const T& value_, std::shared_ptr<Node>& thisNode) noexcept ->  bool
		{
			if (!thisNode)
				return false;

			if (value_ < thisNode->value)
				Node::remove_node(value_, thisNode->left_);
			if (value_ > thisNode->value)
				Node::remove_node(value_, thisNode->right_);
			if (value_ == thisNode->value)
			{
				if (!thisNode->left_ && !thisNode->right_)
				{
					thisNode = nullptr;
					return true;
				}
				else if (thisNode->left_ && !thisNode->right_)
				{
					thisNode = thisNode->left_;
					return true;
				}
				else if (!thisNode->left_ && thisNode->right_)
				{
					thisNode = thisNode->right_;
					return true;
				}
				else
				{
					std::shared_ptr<Node> newRight = thisNode->right_;
					thisNode = thisNode->left_;
					std::shared_ptr<Node> newThisNode = thisNode;
					while (newThisNode->right_)
						newThisNode = newThisNode->right_;
					newThisNode->right_ = newRight;
					return true;
				}
			}
		}

		friend auto copy(std::shared_ptr<Node> tree1, std::shared_ptr<Node> tree) -> std::shared_ptr<Node>
		{
			if (tree1->value != tree->value)
				tree1->value = tree->value;

			if (!tree1->left_ && tree->left_)
				tree1->left_ = std::make_shared<Node>(tree->left_->value);
			if (!tree1->right_ && tree->right_)
				tree1->right_ = std::make_shared<Node>(tree->right_->value);

			if (tree1->left_ && !tree->left_)
				tree1->left_ = nullptr;
			if (tree1->right_ && !tree->right_)
				tree1->right_ = nullptr;

			if (tree1->left_)
				tree1->left_ = copy(tree1->left_, tree->left_);
			if (tree1->right_)
				tree1->right_ = copy(tree1->right_, tree->right_);

			return tree1;
		}

		~Node()
		{
			left_ = nullptr;
			right_ = nullptr;
		}
	};

	BinarySearchTree() : root_(nullptr), size_(0) {}
	BinarySearchTree(const std::initializer_list<T>& list) : size_(list.size()), root_(nullptr)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
			insert(*it);
	}

	BinarySearchTree(BinarySearchTree&& tree) : size_(tree.size_), root_(tree.root_)
	{
		tree.size_ = 0;
		tree.root_ = nullptr;
	};
	BinarySearchTree(const BinarySearchTree& tree) : size_(tree.size_), root_(std::make_shared<Node>(0))
	{
		root_ = copy(root_, tree.root_);
	};

	auto size() const noexcept->size_t
	{
		return size_;
	};
	auto insert(const T& value) -> bool
	{
		bool foundPlace = false;
		if (root_ == nullptr) {
			root_ = std::make_shared<Node>(value);
			return true;
		}
		std::shared_ptr<Node> thisNode = root_;
		while (!foundPlace)
		{
			if (value == thisNode->value)
				throw l_error("element already exists");
			if (value < thisNode->value)
			{
				if (!thisNode->left_)
				{
					thisNode->left_ = std::make_shared<Node>(value);
					foundPlace = true;
				}
				else
					thisNode = thisNode->left_;
			}
			else if (!thisNode->right_)
			{
				thisNode->right_ = std::make_shared<Node>(value);
				foundPlace = true;
			}
			else
				thisNode = thisNode->right_;
		}
		size_++;
		return foundPlace;
	};
	auto find(const T& value) const -> const T*
	{
		if (!root_)
		throw l_error("empty tree");
	std::shared_ptr<Node> thisNode = root_;
	while (1)
	{
		if (value == thisNode->value)
		{
			return &thisNode->value;
		}
		else if (value < thisNode->value)
			if (thisNode->left_)
				thisNode = thisNode->left_;
			else { throw l_error("element not found"); }
		else {
			if (thisNode->right_)
				thisNode = thisNode->right_;
			else
				throw l_error("element not found");
		}
	}
	};
	auto remove(const T& value) -> bool
	{
		bool foundValue = false;
		if (root_)
			foundValue = Node::remove_node(value, root_);
		else
			throw l_error("empty tree");
		if (foundValue)
		{
			size_--;
			return true;
		}
		else
			throw l_error("element not found");
	};

	auto RCL(std::ostream& out, std::shared_ptr<Node> node) const noexcept -> bool
	{
		if (node)
		{
			RCL(out, node->right_);
			out << node->value << ' ';
			RCL(out, node->left_);
			return true;
		}
		else return false;
	}

	auto CLR(std::ofstream& out, std::shared_ptr<Node> node) const noexcept -> bool
	{
		if (node)
		{
			out << node->value << ' ';
			CLR(out, node->left_);
			CLR(out, node->right_);
			return true;
		}
		else return false;
	}

	friend auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&
	{
		tree.RCL(out, tree.root_);
		return out;
	}

	friend auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&
	{
		tree.LCR(out, tree.root_);
		return out;
	}

	friend auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&
	{
		T value;
		while (in >> value) tree.insert(value);
		return in;
	}

	auto operator = (BinarySearchTree&& tree)->BinarySearchTree&
	{
		if (this == &tree)
			return *this;

		size_ = tree.size_;
		tree.size_ = 0;
		root_ = tree.root_;
		tree.root_ = nullptr;
		return *this;
	};
	auto operator = (const BinarySearchTree& tree) -> BinarySearchTree&
	{
		if (this == &tree) return *this;
		else
		{
			root_ = nullptr;
			size_ = tree.size_;
			root_ = tree.root_->copy();
			return *this;
		}
	};
	auto operator == (const BinarySearchTree& tree) -> bool
	{
		return (root_->equal(tree.root_));
	};

	~BinarySearchTree()
	{
		root_ = nullptr;
		size_ = 0;
	};

private:
	size_t size_;
	std::shared_ptr<Node> root_;
};
