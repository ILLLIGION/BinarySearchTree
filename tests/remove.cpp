#include <iostream>
#include <fstream>
#include <memory>

template <typename T>
class BinarySearchTree
{
public:
	struct Node
	{
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		T value;

		Node(T value_) : value(value_), left(nullptr), right(nullptr) {}

		auto _value() const noexcept -> T { return value; }

		auto RCL(std::ostream& out, std::shared_ptr<Node> node) const noexcept -> bool
		{
			if (node)
			{
				RCL(out, node->right);
				out << node->value << ' ';
				RCL(out, node->left);
				return true;
			}
			else return false;
		}

		auto CLR(std::ofstream& out, std::shared_ptr<Node> node) const noexcept -> bool
		{
			if (node)
			{
				out << node->value << ' ';
				CLR(out, node->left);
				CLR(out, node->right);
				return true;
			}
			else return false;
		}

		auto equal(std::shared_ptr<Node> rhs) const noexcept -> bool
		{
			if ((left && !rhs->left) || (right && !rhs->right))
				return false;
			if ((!left && rhs->left) || (!right && rhs->right))
				return false;

			bool equalLeft = true; bool equalRight = true;
			if (value != rhs->value)
				return false;
			else
			{
				if (!left && !right)
					return true;
				if (left)
					equalLeft = left->equal(rhs->left);
				if (right)
					equalRight = right->equal(rhs->right);
				return equalLeft && equalRight;
			}
		}

		static auto remove_node(const T& value_, std::shared_ptr<Node>& thisNode) noexcept ->  bool
		{
			if (!thisNode)
				return false;

			if (value_ < thisNode->value)
				Node::remove_node(value_, thisNode->left);
			if (value_ > thisNode->value)
				Node::remove_node(value_, thisNode->right);
			if (value_ == thisNode->value)
			{
				if (!thisNode->left && !thisNode->right)
				{
					thisNode = nullptr;
					return true;
				}
				else if (thisNode->left && !thisNode->right)
				{
					thisNode = thisNode->left;
					return true;
				}
				else if (!thisNode->left && thisNode->right)
				{
					thisNode = thisNode->right;
					return true;
				}
				else
				{
					std::shared_ptr<Node> newRight = thisNode->right;
					thisNode = thisNode->left;
					std::shared_ptr<Node> newThisNode = thisNode;
					while (newThisNode->right)
						newThisNode = newThisNode->right;
					newThisNode->right = newRight;
					return true;
				}
			}
		}

		friend auto copy(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) -> std::shared_ptr<Node>
		{
			if (lhs->value != rhs->value) 
				lhs->value = rhs->value;  

			if (!lhs->left && rhs->left) 
				lhs->left = std::make_shared<Node>(rhs->left->value); 
			if (!lhs->right && rhs->right) 
				lhs->right = std::make_shared<Node>(rhs->right->value);

			if (lhs->left && !rhs->left) 
				lhs->left = nullptr;
			if (lhs->right && !rhs->right) 
				lhs->right = nullptr;

			if (lhs->left)
				lhs->left = copy(lhs->left, rhs->left);
			if (lhs->right)
				lhs->right = copy(lhs->right, rhs->right);

			return lhs;
		}

		~Node()
		{
			left = nullptr;
			right = nullptr;
		}
	};

	BinarySearchTree() : root(nullptr), size_(0) {}
	BinarySearchTree(const std::initializer_list<T>& list) : size_(list.size()), root(nullptr)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
			insert(*it);
	}

	BinarySearchTree(BinarySearchTree&& rhs) : size_(rhs.size_), root(rhs.root)
	{
		rhs.size_ = 0;
		rhs.root = nullptr;
	};
	BinarySearchTree(const BinarySearchTree& rhs) : size_(rhs.size_), root(std::make_shared<Node>(0))
	{
		root = copy(root, rhs.root);
	};

	auto size() const noexcept->size_t 
	{ 
		return size_; 
	};
	auto insert(const T& value) noexcept -> bool
	{
		bool foundPlace = false;
		if (root == nullptr) {
			root = std::make_shared<Node>(value);
			return true;
		}
		std::shared_ptr<Node> thisNode = root;
		while (!foundPlace)
		{
			if (value == thisNode->value)
				return false;
			if (value < thisNode->value)
			{
				if (!thisNode->left)
				{
					thisNode->left = std::make_shared<Node>(value);
					foundPlace = true;
				}
				else
					thisNode = thisNode->left;
			}
			else if (!thisNode->right)
			{
				thisNode->right = std::make_shared<Node>(value);
				foundPlace = true;
			}
			else
				thisNode = thisNode->right;
		}
		size_++;
		return foundPlace;
	};
	auto find(const T& value) const noexcept -> const T*
	{
		if (!root)
		return nullptr;
		std::shared_ptr<Node> thisNode = root;
		while (1)
		{
			if (value == thisNode->value)
			{
				return &thisNode->value;
			}
			else if (value < thisNode->value)
			if (thisNode->left)
				thisNode = thisNode->left;
			else { return nullptr;}
			else {
			if (thisNode->right)
				thisNode = thisNode->right;
			else
				return nullptr;
			}
		}
	};
	auto remove(const T& value) noexcept -> bool
	{
		bool foundValue = false;
		if (root)
			foundValue = Node::remove_node(value, root);
		else
			return false;
		if (foundValue)
			size_--;
		return foundValue;
	};

	friend auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&
	{
		tree.RCL(out, tree.root);
		return out;
	}

	friend auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&
	{
		tree.LCR(out, tree.root);
		return out;
	}

	friend auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&
	{
		T value;
		while (in >> value) tree.insert(value);
		return in;
	}

	auto operator = (BinarySearchTree&& rhs)->BinarySearchTree&
	{
		if (this == &rhs)
			return *this;

		size_ = rhs.size_;
		rhs.size_ = 0;
		root = rhs.root;
		rhs.root = nullptr;
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
	auto operator == (const BinarySearchTree& rhs) -> bool
	{
		if (root->equal(rhs.root))
			return true;
		else
			return false;
	};

	~BinarySearchTree()
	{
		root = nullptr;
		size_ = 0;
	};

private:
	size_t size_;
	std::shared_ptr<Node> root;
};
