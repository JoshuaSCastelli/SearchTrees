#pragma once


#include <iostream>

class BST {
public:

	class node {
	public:
		node * left = nullptr;
		node * right = nullptr;
		node * parent = nullptr;
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

	BST() {
		root = new node;
	};
	void inorderTreeWalk(node * root);
	node iterativeTreeSearch(node * root, string key);
	node treeMin(node * root);
	node treeMax(node * root);
	node treeSuccessor(node * root);
	node treePredecessor(node * root);
	void treeInsert(BST* tree, BST::node * z);
	void treeDelete(BST* tree, node*z);
	void treeTransplant(BST* tree, node*u, node*v);
	void buildTree(BST* tree,string * list, int size);
	

};