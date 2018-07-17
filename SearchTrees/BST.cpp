
#include "stdafx.h"
#include "BST.h"

/*Walks through the tree in-order*/
void BST::inorderTreeWalk(node * root) {
	if (root != nullptr) {
		inorderTreeWalk(root->left);
		cout << root->key << endl;
		inorderTreeWalk(root->right);
	}
};
/*Searches the tree for input key*/
BST::node BST::iterativeTreeSearch(node*root, string key) {
	while (root != nullptr && key != root->key) {
		if (key < root->key) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	/////
	if (root == nullptr) {
		node * temp = new node;
		temp->key = "";
		return *temp;
	}
	else {
		return *root;
	}
};
/*Finds the minimum value from he given root node*/
BST::node BST::treeMin(node * root) {
	while (root->left != nullptr) {
		root = root->left;
	}
	return *root;
};
/*Finds the maximum value from the given root node*/
BST::node BST::treeMax(node * root) {
	while (root->right != nullptr) {
		root = root->right;
	}
	return *root;
};
/*Finds Successor of given node*/
BST::node BST::treeSuccessor(node * root) {
	if (root->right != nullptr) {
		return treeMin(root->right);
	}
	node * y = root->parent;
	while (y != nullptr && root == y->right) {
		root = y;
		y = y->parent;
	}
	return *y;
};
/*Finds Predecessor of given node*/
BST::node BST::treePredecessor(node * root) {
	if (root->left != nullptr) {
		return treeMax(root->left);
	}
	node * y = root->parent;
	while (y != nullptr && root == y->left) {
		root = y;
		y = y->parent;
	}
	return *y;
};
/*Inserts node into tree*/
void BST::treeInsert(BST * tree, BST::node * z) {
	BST::node * y;
	y = nullptr;
	BST::node * x;
	x = tree->root;
	while (x != nullptr) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;
	if (y == nullptr) {
		tree->root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}
}
/*Deletes node from tree*/
void BST::treeDelete(BST* tree, node*z) {
	if (z->left == nullptr) {
		treeTransplant(tree, z, z->right);
	}
	else if (z->right == nullptr) {
		treeTransplant(tree, z, z->left);
	}
	else {///////////////////////////////////////////////////////////////////
		node y = treeMin(z->right);
		if (y.parent != z) {
			treeTransplant(tree, &y, y.right);
			y.right = z->right;
			y.right->parent = &y;
		}
		treeTransplant(tree, z, &y);
		y.left = z->left;
		y.left->parent = &y;
	}
};
/*Used in association with the treeDelete function to replace the subrree rooted at node u, with the subtree rooted at node v*/
void BST::treeTransplant(BST* tree, node*u, node*v) {
	if (u->parent == nullptr) {
		tree->root = v;
	}else if(u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
};
/*Constructs the Binary search tree from a given string array*/
void BST::buildTree(BST * tree,string* list, int size) {
	for (int i = 0; i < size; i++) {
		BST::node * z;
		z = new BST::node;
		z->key = list[i];
		treeInsert(tree,z);
	}
};

/*Relational/Equality operators override */
string BST::node::toString()const {
	return key;
};
bool BST::node::operator == (const node& o) const { return (this->key == o.key); };
bool BST::node::operator !=(const node& o) const { return (this->key != o.key); };
bool BST::node::operator <(const node& o) const { return (this->key < o.key); };
bool BST::node::operator <=(const node& o) const { return (this->key <= o.key); };
bool BST::node::operator >(const node& o) const { return (this->key > o.key); };
bool BST::node::operator >=(const node& o) const { return (this->key >= o.key); };