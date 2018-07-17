
#include "RBT.h"
#include "stdafx.h"


/*Walks through the tree in-order*/
void RBT::inorderTreeWalk(node * root) {
	if (root != nullptr) {
		inorderTreeWalk(root->left);
		cout << root->key << endl;
		inorderTreeWalk(root->right);
	}
};
/*Searches the tree for input key*/
RBT::node RBT::iterativeTreeSearch(node*root, string key) {
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
		delete temp;
	}
	else {
		return *root;
	}
};
/*Finds the minimum value from he given root node*/
RBT::node RBT::treeMin(node * root) {
	while (root->left != nullptr) {
		root = root->left;
	}
	return *root;
};
/*Finds the maximum value from the given root node*/
RBT::node RBT::treeMax(node * root) {
	while (root->right != nullptr) {
		root = root->right;
	}
	return *root;
};
/*Finds Successor of given node*/
RBT::node RBT::treeSuccessor(node * root) {
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
RBT::node RBT::treePredecessor(node * root) {
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
/*Rotates tree left*/
void RBT::leftRotate(RBT*tree, RBT::node * root) {
	RBT::node * y = root->right;
	root->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = root;
	}
	y->parent = root->parent;
	if (root->parent == nullptr) {
		tree->root = y;
	}
	else if (root == root->parent->left) {
		root->parent->left = y;
	}
	else {
		root->parent->right = y;
	}
	y->left = root;
	root->parent = y;
};
/*Rotates tree right*/
void RBT::rightRotate(RBT*tree, RBT::node * root) {
	RBT::node * y = root->left;
	root->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = root;
	}
	y->parent = root->parent;
	if (root->parent == nullptr) {
		tree->root = y;
	}
	else if (root == root->parent->right) {
		root->parent->right = y;
	}
	else {
		root->parent->left = y;
	}
	y->right = root;
	root->parent = y;
};
/*Inserts node into tree*/
void RBT::treeInsert(RBT * tree, RBT::node * z) {
	RBT::node * y;
	y = nullptr;
	RBT::node * x;
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
	z->left = nullptr;
	z->right = nullptr;
	z->color = "red";
	insertFixup(tree, z);
}
/*Maintains RB properties after insertion*/
void RBT::insertFixup(RBT * tree, RBT::node * z) {
	while (z->parent != nullptr && z->parent->color == "red") {
		if (z->parent == z->parent->parent->left) {
			RBT::node * y = z->parent->parent->right;
			if (y != nullptr && y->color == "red") {
				z->parent->color = "black";
				y->color = "black";
				z->parent->parent->color = "red";
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					leftRotate(tree, z);
				}
				z->parent->color = "black";
				z->parent->parent->color = "red";
				rightRotate(tree, z->parent->parent);
			}
		}
		else {
			RBT::node * y = z->parent->parent->left;
			if (y != nullptr && y->color == "red") {
				z->parent->color = "black";
				y->color = "black";
				z->parent->parent->color = "red";
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rightRotate(tree, z);
				}
				z->parent->color = "black";
				z->parent->parent->color = "red";
				leftRotate(tree, z->parent->parent);
			}
		}
	}
	tree->root->color = "black";
};
/*Deletes node from tree*/
void RBT::treeDelete(RBT* tree, node*z) {
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
void RBT::treeTransplant(RBT* tree, node*u, node*v) {
	if (u->parent == nullptr) {
		tree->root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
};
/*Constructs the Binary search tree from a given string array*/
void RBT::buildTree(RBT* tree, string * list, int size) {
	//tree->root->key = list[0];
	//tree->root->color = "black";
	for (int i = 0; i < size; i++) {
		RBT::node * z;
		z = new RBT::node;
		z->key = list[i];
		treeInsert(tree, z);
	}
};

/*Relational/Equality operators override */
string RBT::node::toString()const {
	return key;
};
bool RBT::node::operator == (const node& o) const { return (this->key == o.key); };
bool RBT::node::operator !=(const node& o) const { return (this->key != o.key); };
bool RBT::node::operator <(const node& o) const { return (this->key < o.key); };
bool RBT::node::operator <=(const node& o) const { return (this->key <= o.key); };
bool RBT::node::operator >(const node& o) const { return (this->key > o.key); };
bool RBT::node::operator >=(const node& o) const { return (this->key >= o.key); };