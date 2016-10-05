#pragma once
#include <iostream>
#include <fstream>

template <typename T>
class BinarySearchTree {
public:
	struct Node {
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}
		void copy(Node* node) const noexcept
		{
			value_ = node->value_;
			delete left_;
			delete left_;
			if (node->left_)
				left_ = new Node(node->left_->value_);
			else
				left_ = nullptr;
			if (node->right_)
				right_ = new Node(node->right_->value_);
			else
				right_ = nullptr;
			if (left_)
				left_->copy(node->left_);
			if (right_)
				right_->copy(node->right_);
		}
		Node * left_;
		Node * right_;
		T value_;
		auto compare(Node* node) const noexcept -> bool

		{
			bool equalityL, equalityR;
			if (left_ && !node->left_) 	return false;
			if (right_ && !node->right_) return false;
			if (!left_ && node->left_) return false;
			if (!right_ && node->right_) return false;
			if (value_ != node->value_) return false;
			if (!left_ && !right_) return true;
			if (left_)
				equalityL = left_->compare(node->left_);
			if (right_)
				equalityR = right_->compare(node->right_);
			return (equalityL && equalityR);
		}

		~Node()
		{
			delete left_; left_ = nullptr;
			delete right_; right_ = nullptr;
		};
	};

	BinarySearchTree() : root_(nullptr), size_(0) {};

	BinarySearchTree(const std::initializer_list<T> & list) : BinarySearchTree()
	{
		for (auto& value : list)
			insert(value);
	};

	BinarySearchTree(const BinarySearchTree& tree) : size_(tree.size_), root_(nullptr)
	{
		root_ = new Node(0);
		root_->copy(tree.root_);
	}

	BinarySearchTree(BinarySearchTree&& tree) : size_(tree.size_), root_(tree.root)
	{
		tree.root = nullptr;
		tree.size = 0;
	}

	~BinarySearchTree()
	{
		delete root_; root_ = nullptr;
		size_ = 0;
	};
	auto size() const noexcept -> size_t
	{
		return size_;
	};
	auto insert(const T & value) noexcept -> bool
	{
		if (size_ == 0)
		{
			root_ = new Node(value);
			size_ = 1;
			return true;
		}
		Node* curNode = root_;
		Node* prevNode = nullptr;
		while (curNode)
		{
			prevNode = curNode;
			if (value == curNode->value_) return false;
			if (value < curNode->value_) curNode = curNode->left_;
			else curNode = curNode->right_;
		}
		if (value < prevNode->value_) prevNode->left_ = new Node(value);
		else prevNode->right_ = new Node(value);
		size_++;
		return true;
	};
	auto find(const T & value) const noexcept -> const T *
	{
		if (size_ == 0) return nullptr;
	Node* curNode = root_;
	do
	{
		if (value == curNode->value_) return &curNode->value_;
		else if (value < curNode->value_) curNode = curNode->left_;
		else if (value > curNode->value_) curNode = curNode->right_;
	} while (curNode);
	return nullptr;
	};

	auto RCL(std::ostream& out, Node* node) const noexcept -> bool
	{
		if (node)
		{
			RCL(out, node->right_);
			out << node->value_ << ' ';
			RCL(out, node->left_);
			return true;
		}
		else return false;
	}

	auto CLR(std::ofstream& out, Node* node) const noexcept -> bool
	{
		if (node)
		{
			out << node->value_ << ' ';
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
		tree.CLR(out, tree.root_);
		return out;
	}

	friend auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&
	{
		T value;
		while (in >> value) tree.insert(value);
		return in;
	}
	friend auto operator >> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&
	{
		T value;
		while (in >> value) tree.insert(value);
		return in;
	}

	auto BinarySearchTree<T>::operator= (BinarySearchTree<T>&& tree) -> BinarySearchTree<T>&
	{
		if (this == &tree)
			return *this;

		delete root_;
		size_ = tree.size_;
		root_ = tree.root_;
		tree.root_ = nullptr;
		tree.size_ = 0;
		return *this;
	}

	auto BinarySearchTree<T>::operator= (const BinarySearchTree<T>& tree) -> BinarySearchTree<T>&
	{
		if (this == &tree)
			return *this;

		if (tree.root_)
		{
			root_ = new Node(root_->copy(tree.root_)); //left_ = new Node(node->left_->value_);
		}
		else
		{
			delete root_;
			root_ = nullptr;
		}
		size_ = tree.size_;
		return *this;
	}

	auto operator == (const BinarySearchTree& tree) -> bool
	{
		return root_->compare(tree.root_);
	}

private:
	Node * root_;
	size_t size_;
};

