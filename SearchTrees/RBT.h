#pragma once

#include <iostream>
#include <string>

class RBT {
public:
	
	class node {
	public:
		node * left = nullptr;
		node * right = nullptr;
		node * parent = nullptr;
		string color;
		string key;

		string toString() const;
		virtual bool operator ==(const node& o) const;
		virtual bool operator !=(const node& o) const;
		virtual bool operator <(const node& o) const;
		virtual bool operator <=(const node& o) const;
		virtual bool operator >(const node& o) const;
		virtual bool operator >=(const node& o) const;
	};
	node*root;

	RBT() {
		root = new node;
	};
	void inorderTreeWalk(node * root);
	node iterativeTreeSearch(node * root, string key);
	node treeMin(node * root);
	node treeMax(node * root);
	node treeSuccessor(node * root);
	node treePredecessor(node * root);
	void leftRotate(RBT*tree, RBT::node * root);
	void rightRotate(RBT*tree, RBT::node * root);
	void treeInsert(RBT* tree, RBT::node * z);
	void insertFixup(RBT* tree, node* z);
	void treeDelete(RBT* tree, node*z);
	void treeTransplant(RBT* tree, node*u, node*v);
	void buildTree(RBT* tree, string * list, int size);


};