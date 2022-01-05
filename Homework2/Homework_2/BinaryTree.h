#pragma once

template <typename T>
class BinaryTree {
private:
	//data
	struct Node
	{
		T value;
		Node* left, * right;

		Node(const T& value, Node* left = nullptr, Node* right = nullptr)
			: value(value), left(left), right(right)
		{}
	}*root;

	size_t size;
	//
	void clear(Node* root);
	Node* copy(Node* root);
	Node* getMin(Node*& root);
	int height(const Node* root) const;
	Node* findNode(const T& val, Node* root) const;
	Node* insertNode(const T& val, Node* root);
	Node* deleteNode(const T& val, Node* root);
	//AVL
	Node* balanceTree(const T& val, Node* node);
	Node* rightRotate(Node* root);
	Node* leftRotate(Node* root);
	void print(Node* root, Node* parent = nullptr, bool isLeft = true) const;

public:
	//constr and operators
	BinaryTree();
	BinaryTree(const BinaryTree& other);
	BinaryTree(const BinaryTree&& other) noexcept;
	~BinaryTree();
	BinaryTree& operator=(const BinaryTree& other);
	BinaryTree& operator=(BinaryTree&& other) noexcept;
	//
	T& find(const T& val) const;
	void insert(const T val);
	bool remove(const T& val);

	size_t getSize() const;
	size_t getHeight() const;
	void print() const;
	void clearData();
};

template<typename T>
void BinaryTree<T>::clearData() 
{
	clear(root);
}

template<typename T>
void BinaryTree<T>::print() const
{
	print(root);
}

template<typename T>
void BinaryTree<T>::print(Node* root, Node* parent, bool isLeft) const
{
	if (root) {
		if (parent) std::cout << parent->value << "->" << root->value << (isLeft ? "(left)\n" : "(right)\n");
		print(root->left, root);
		print(root->right, root, false);
	}
}


template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T> ::deleteNode(const T& val, Node* root)
{
	if (!root)
		return root;

	if (val < root->value) {
		root->left = deleteNode(val, root->left);
	}

	else if (val > root->value) {
		root->right = deleteNode(val, root->right);
	}
	else
	{
		//one child cases
		if (!root->left || !root->right)
		{
			Node* temp = root->left ? root->left : root->right;

			if (!temp)
			{
				temp = root;
				root = nullptr;
			}
			else
			{
				*root = *temp;
			}

			delete temp;
		}
		else
		{
			Node* temp = getMin(root->right);
			root->value = temp->value;
			root->right = deleteNode(temp->value, root->right);
		}
		--size;
	}

	if (!root)
		return root;

	return balanceTree(val, root);
}


template<typename T>
size_t BinaryTree<T>::getHeight() const
{
	return height(root);
}

template<typename T>
void BinaryTree<T>::clear(Node* root)
{
	if (root) {
		clear(root->left);
		clear(root->right);
		delete root;
	}
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copy(Node* root)
{
	return root ? new Node(root->value, copy(root->left), copy(root->right)) : root;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::getMin(Node*& root)
{
	if (root->left) {
		return getMin(root->left);
	}

	Node* lastRoot = root;
	root = root->right;
	return lastRoot;
}

template<typename T>
int BinaryTree<T>::height(const Node* root) const
{
	if (!root) return 0;
	int leftH = height(root->left);
	int rightH = height(root->right);
	return 1 + (leftH > rightH ? leftH : rightH);
}


template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findNode(const T& val, Node* root) const
{
	if (!root) return nullptr;
	if (root->value == val) return root;
	return val < root->value ? findNode(val, root->left) : findNode(val, root->right);
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insertNode(const T& val, Node* root)
{

	if (root == nullptr) {
		++size;
		return new Node(val);
	}
	if (val < root->value) {
		root->left = insertNode(val, root->left);
	}
	else if(val>root->value){
		root->right = insertNode(val, root->right);
	}
	else {//equal not permitted
		throw std::logic_error("Node already exists");
	}
	return balanceTree(val, root);
}


template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::balanceTree(const T& val, Node* node)
{
	int balance = height(node->left) - height(node->right);

	if (balance > 1 && val < node->left->value) {
		return rightRotate(node);
	}

	if (balance < -1 && val > node->right->value) {
		return leftRotate(node);
	}

	if (balance > 1 && val > node->left->value) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && val < node->right->value) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::rightRotate(Node* root)
{
	Node* leftNode = root->left;
	Node* farRight = leftNode->right;

	leftNode->right = root;
	root->left = farRight;

	return leftNode;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::leftRotate(Node* root)
{
	Node* rightNode = root->right;
	Node* farLeft = rightNode->left;

	rightNode->left = root;
	root->right = farLeft;

	return rightNode;
}

template<typename T>
BinaryTree<T>::BinaryTree()
	:root(nullptr), size(0)
{}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
{
	root = copy(root);
	size = other.getSize();
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree&& other) noexcept
	:root(other.root), size(other.size)
{
	other.root = nullptr;
	other.size = 0;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	clear(root);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other)
{
	if (&other != this) {
		clear(root);
		root = copy(other.root);
		size = other.size;
	}
	return *this;
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree&& other) noexcept
{
	if (&other != this) {
		root = other.root;
		other.root = nullptr;
		size = other.size;
		other.size = 0;
	}
	return *this;
}

template<typename T>
T& BinaryTree<T>::find(const T& val) const
{
	Node* node = findNode(val, root);
	if (!node) throw - 1;
	return  node->value;
}

template<typename T>
void BinaryTree<T>::insert(const T val)
{
	root = insertNode(val, root);
}

template<typename T>
bool BinaryTree<T>::remove(const T& val)
{
	return deleteNode(val, root);
}

template<typename T>
size_t BinaryTree<T>::getSize() const
{
	return size;
}
