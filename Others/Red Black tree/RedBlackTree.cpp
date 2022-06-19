#include "RedBlackTree.h"

void RBTree::leftRotate(Node*& node) noexcept
{
	Node* y = node->right;

	node->right = y->left;

	if (node->right)
		node->right->parent = node;

	y->parent = node->parent;

	if (!node->parent)
	{
		root = y;
		//root->parent = nullptr;
	}

	else if (node == node->parent->left)
		node->parent->left = y;

	else
		node->parent->right = y;

	y->left = node;
	node->parent = y;

}

void RBTree::rightRotate(Node*& node) noexcept
{
	Node* y = node->left;

	node->left = y->right;


	if (node->left)
		node->left->parent = node;

	y->parent = node->parent;

	if (!node->parent)
	{
		root = y;
		//root->parent = nullptr;
	}

	else if (node == node->parent->left)
		node->parent->left = y;

	else
		node->parent->right = y;

	y->right = node;
	node->parent = y;
}

void RBTree::correctInsertion(Node*& node) noexcept
{
	Node* parent = NULL;
	Node* grandParent = NULL;

	while ((node != root) && (node->isRed) && (node->parent->isRed))
	{
		parent = node->parent;
		grandParent = node->parent->parent;

		//left child of grandparent
		if (parent == grandParent->left)
		{
			//uncle is red
			if (grandParent->right != NULL && grandParent->right->isRed)
			{
				grandParent->isRed = true;
				parent->isRed = false;
				grandParent->right->isRed = false;
				node = grandParent;
			}

			else
			{
				//node is right parent - rotate left
				//black triangle
				if (node == parent->right)
				{
					leftRotate(parent);
					node = parent;
					parent = node->parent;
				}

				//black line
				rightRotate(grandParent);
				std::swap(parent->isRed,
					grandParent->isRed);
				node = parent;
			}
		}

		//right child - mirror case
		else
		{
			//red left uncle
			if ((grandParent->left != NULL) && (grandParent->left->isRed))
			{
				grandParent->isRed = true;
				parent->isRed = false;
				grandParent->left->isRed = false;//black uncle
				node = grandParent;
			}
			else
			{
				//black triangle
				if (node == parent->left)
				{
					rightRotate(parent);
					node = parent;
					parent = node->parent;
				}

				//black line
				leftRotate(grandParent);
				std::swap(parent->isRed, grandParent->isRed);
				node = parent;
			}
		}
	}

	root->isRed = false;
}

void RBTree::deleteAll(Node* node) noexcept
{
	if (!node) return; //for when root is nullptr
	if (node->left) {
		deleteAll(node->left);
	}
	if (node->right) {
		deleteAll(node->right);
	}
	delete node;
}

bool RBTree::removeNode(Node* node) noexcept
{
	//
	Node* u = findReplace(node);

	// True when u and v are both black
	bool bothAreBlack = ((u == nullptr || u->isRed == false) && (node->isRed == false));
	Node* parent = node->parent;

	if (!u) {
		//u is null so node is leaf
		if (node == root) {
			// node is root, making root nullptr
			root = nullptr;
		}
		else {
			if (bothAreBlack) {
				// u and v both black
				// v is leaf, fix double black at v
				fixBlackNode(node);
			}
			else {
				// u or v is red
				if (getSibling(node))
					// sibling is not null, make it red"
					getSibling(node)->isRed = true;
			}

			// delete v from the tree
			if (node == node->parent->left) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		delete node;
		return true;
	}

	if (!node->left || !node->right) {
		// v has 1 child
		if (node == root) {
			// v is root, assign the value of u to v, and delete u
			node->value = u->value;
			node->left = nullptr;
			node->right = nullptr;
			delete u;
		}
		else {
			// Detach v from tree and move u up
			if (node == node->parent->left) {
				parent->left = u;
			}
			else {
				parent->right = u;
			}
			delete node;
			u->parent = parent;
			if (bothAreBlack) {
				// u and v both black, fix double black at u
				fixBlackNode(u);
			}
			else {
				// u or v red, color u black
				u->isRed = false;
			}
		}
		return true;
	}

	// v has 2 children, swap values with successor and recurse
	std::swap(u->value, node->value);
	//std::swap(u, node);
	removeNode(u);
}



inline Node* RBTree::getSibling(Node* node) const noexcept
{
	//no parent, no sibling
	if (!node->parent)
		return nullptr;

	if (node == node->parent->left)
		return node->parent->right;

	return node->parent->left;
}

Node* RBTree::findReplace(Node* node) const noexcept
{
	if (node->left && node->right) //2 children
	{//get the last left child of right node
		Node* searched = node->right;

		while (searched->left)
			searched = searched->left;

		return searched;
	}

	//leaf
	if (!node->left && !node->right)
		return nullptr;

	//has single child
	if (!node->left)
		return node->left;
	else
		return node->right;
}

void RBTree::fixBlackNode(Node* node) noexcept
{
	if (node == root)
		return;

	Node* sibling = getSibling(node);//, * parent = x->parent;
	Node* parent = node->parent;
	if (!sibling) {
		// No sibiling, double black pushed up
		fixBlackNode(node->parent);
	}
	else {
		if (sibling->isRed) {
			// Sibling red
			node->parent->isRed = true;
			sibling->isRed = false;
			if (sibling == sibling->parent->left) {
				// left case
				rightRotate(node->parent);
			}
			else {
				// right case
				leftRotate(node->parent);
			}
			fixBlackNode(node);
		}
		else {
			// Sibling black
			if ((sibling->left && sibling->left->isRed) ||
				(sibling->right && sibling->right->isRed)) {
				// at least 1 red children
				if (sibling->left && sibling->left->isRed) {
					if (sibling == sibling->parent->left) {
						// left left
						sibling->left->isRed = sibling->isRed;
						sibling->isRed = node->parent->isRed;
						rightRotate(node->parent);
					}
					else {
						// right left
						sibling->left->isRed = node->parent->isRed;
						rightRotate(sibling);
						leftRotate(node->parent);
					}
				}
				else {
					if (sibling == sibling->parent->left) {
						// left right
						sibling->right->isRed = node->parent->isRed;
						leftRotate(sibling);
						rightRotate(node->parent);
					}
					else {
						// right right
						sibling->right->isRed = sibling->isRed;
						sibling->isRed = node->parent->isRed;
						leftRotate(node->parent);
					}
				}
				parent->isRed = false;
			}
			else {
				// 2 black children
				sibling->isRed = true;
				if (node->parent->isRed == false)
					fixBlackNode(node->parent);
				else
					node->parent->isRed = false;
			}
		}
	}
}

Node* RBTree::makeCopy(const Node* current)
{
	if (!current) return nullptr;
	Node* node = nullptr;
	node = new Node(current->value, current->isRed);//may throw
	try {
		node->left = makeCopy(current->left);
	}
	catch (...) {
		delete node;
		throw;
	}
	try {
		node->right = makeCopy(current->right);
	}
	catch (...) {
		delete node;
		deleteAll(node->left);
		throw;
	}
	return node;
}

void RBTree::moveSubtrees(Node* place, Node* tree) noexcept
{
	if (!place->parent) {
		root = tree;
	}
	else if (place == place->parent->left) {
		place->parent->left = tree;
	}
	else {
		place->parent->right = tree;
	}
	tree->parent = place->parent;
}

RBTree::RBTree(const RBTree& other)
{
	root = makeCopy(other.root);
	//if root=nullptr -> problem with allocation
}

RBTree::RBTree(RBTree&& other) noexcept
	:RBTree()
{
	std::swap(other.size, this->size);
	std::swap(other.root, this->root);

}

RBTree& RBTree::operator=(const RBTree& other)
{
	if (&other != this) {
		Node* newRoot = makeCopy(other.root);
		deleteAll(root);
		root = newRoot;
	}
	return *this;
}

RBTree& RBTree::operator=(RBTree&& other) noexcept
{

	if (&other != this) {
		deleteAll(root);
		size = 0;
		std::swap(other.size, this->size);
		std::swap(other.root, this->root);
	}
	return *this;
}

RBTree::~RBTree() noexcept
{
	if (root) {
		deleteAll(root);
		size = 0;
		root = nullptr;
	}
}

size_t RBTree::getSize() const noexcept
{
	return size;
}

bool RBTree::insert(int key) noexcept
{
	Node* newNode = nullptr;
	try {
		newNode = new Node(key, true);
	}
	catch (...) {
		return false;//couldnt insert 
	}
	if (!root) {
		root = newNode;
		root->isRed = false;
	}
	else {
		//find the right parent
		findPlace(newNode);
		// fix RB rules
		correctInsertion(newNode);
	}
	++size;
	return true;
}

inline void RBTree::findPlace(Node* newNode) noexcept
{
	Node* node = root;
	Node* parent = nullptr;
	while (node)
	{
		parent = node;
		if (newNode->value < node->value) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	newNode->parent = parent;
	if (newNode->value < parent->value) { //place in the correct side
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
}

bool RBTree::remove(int key) noexcept
{
	//we should find it
	Node* helper = root;
	//
	while (helper) {
		if (helper->value == key) {
			break;
		}
		if (key < helper->value) {
			if (!helper->left) break;
			helper = helper->left;
		}
		else {
			if (!helper->right) break;
			helper = helper->right;
		}
	}
	if (helper && helper->value == key && removeNode(helper)) {
		--size;
		return true;
	}
	return false;//couldnt find

}

bool RBTree::exists(int key) const noexcept
{
	Node* node = root;
	while (node) {
		if (node->value == key) {
			return true;
		}
		if (node->value > key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return false;
}
