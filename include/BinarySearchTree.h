#pragma once
#include <iostream>
#include <fstream>
#include <memory>

template <typename T>
class BinarySearchTree {
public:
	struct Node {
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}
		auto copy(std::shared_ptr<Node> node) noexcept -> std::shared_ptr<Node>
		{
			value_ = node->value_;
			if (node->left_)
				left_ = node->left_;
			else
				left_ = nullptr;
			if (node->right_)
				right_ = node->right_;
			else
				right_ = nullptr;
			if (left_)
				left_->copy(node->left_);
			if (right_)
				right_->copy(node->right_);

			return std::make_shared<Node>(this);
		}
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		T value_;
		auto compare(std::shared_ptr<Node> node) const noexcept -> bool

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

		static auto remove_node(const T& value, std::shared_ptr<Node>& thisNode) noexcept ->  bool
        {
            if (!thisNode)
                return false;

            if (value < thisNode->value_)
                Node::remove_node(value, thisNode->left_);
            if (value > thisNode->value_)
                Node::remove_node(value, thisNode->right_);
            if (value == thisNode->value_)
            {
                if (!thisNode->left_ && !thisNode->right_)
                {
                    thisNode = nullptr;
                    return true;
                } else if (thisNode->left_ && !thisNode->right_)
                {
                    thisNode = thisNode->left_;
                    return true;
                } else if (!thisNode->left_ && thisNode->right_)
                {
                    thisNode = thisNode->right_;
                    return true;
                } else
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

		~Node()
		{
			left_ = nullptr;
			right_ = nullptr;
		};
	};

	BinarySearchTree() : root_(nullptr), size_(0) {};

	BinarySearchTree(const std::initializer_list<T> &list) : size_(list.size()), root_(nullptr)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
			insert(*it);
	}

	BinarySearchTree(const BinarySearchTree& tree) : size_(tree.size_), root_(std::make_shared<Node>(nullptr))
	{
		root_ = root_->copy(tree.root_);
	}

	BinarySearchTree(BinarySearchTree&& tree) : size_(tree.size_), root_(tree.root)
	{
		tree.root = nullptr;
		tree.size = 0;
	}

	~BinarySearchTree()
	{
		root_ = nullptr;
		size_ = 0;
	};
	auto size() const noexcept -> size_t
	{
		return size_;
	};
	
	auto insert(const T& value) noexcept -> bool
	{
    		bool result = false;
    		if (root_ == nullptr) 
		{
        		root_ = std::make_shared<Node>(value);
        		return true;
    		}
    		std::shared_ptr<Node> thisNode = root_;
    		while (!result)
    		{
        		if (value == thisNode->value_)
            		return false;
        		if (value < thisNode->value_)
        		{
            			if (!thisNode->left_)
            			{
                			thisNode->left_ = std::make_shared<Node>(value);
                			result = true;
            			} 
				else thisNode = thisNode->left_;
        		} 
			else if (!thisNode->right_)
        		{
            			thisNode->right_ = std::make_shared<Node>(value);
            			result = true;
        		} 
			else
            		thisNode = thisNode->right_;
    		}
    		size_++;
    		return result;
	}

	auto find(const T & value) const noexcept -> const T *
	{
		if (size_ == 0) return nullptr;
	std::shared_ptr<Node> curNode = root_;
	do
	{
		if (value == curNode->value_) return &curNode->value_;
		else if (value < curNode->value_) curNode = curNode->left_;
		else if (value > curNode->value_) curNode = curNode->right_;
	} while (curNode);
	return nullptr;
	};

	auto RCL(std::ostream& out, std::shared_ptr<Node> node) const noexcept -> bool
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

	auto remove(const T& value) noexcept -> bool
	{
		bool result = false;
		if (root_)
			result = Node::remove_node(value, root_);
		else
			return false;
		if (result)
			size_--;
		return result;
	}

	auto CLR(std::ofstream& out, std::shared_ptr<Node> node) const noexcept -> bool
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
        size_t n;
        if (!(in >> n)){
            std::cerr << "wrong type of number of elements" << std::endl;
            return in;
        }
        tree.size_ = n;
        for (int i = 0; i < n; ++i)
        {
            T value;
            if(in >> value)
                tree.insert(value);
            else {
                std::cerr << "wrong input data" << std::endl;
                return in;
            }
        }
        return in;
}

	auto operator=(BinarySearchTree &&tree) -> BinarySearchTree&
	{
		if (this == &tree)
			return *this;

		size_ = tree.size_;
		tree.size_ = 0;

		root_ = tree.root_;
		tree.root_ = nullptr;
		return *this;
	}

	auto operator = (const BinarySearchTree<T>& tree) -> BinarySearchTree<T>&
	{
		if (this == &tree)
			return *this;
		size_ = tree.size_;
		root_->copy(tree.root_);
		return *this;
	}

	auto operator == (const BinarySearchTree& tree) -> bool
	{
		return root_->compare(tree.root_);
	}

private:
	std::shared_ptr<Node> root_;
	size_t size_;
};
