#ifndef CPSC_350_BST_H
#define CPSC_350_BST_H
#include <iostream>
#include "TreeNode.h"
template <typename T>
class BST {
public:
	BST();
	~BST();
	void insertNode(const T& value);
	bool searchNode(const T& value) const;
	const T& getNodeValue(const T& value) const;	// Pre: searchNode(value) returns true
	bool deleteNode(const T& value);
	bool isEmpty() const;
	size_t getSize() const;
	void printTree() const;
	void writePreorder(std::ostream&, void (*write)(std::ostream&, const T& )) const;
	void clear();

private:
	TreeNode<T>* root;
	size_t size;

	TreeNode<T>*& getParent(const T& value);
	static void recPrint(const TreeNode<T>* node);
	static TreeNode<T>* pluckMinNode(TreeNode<T>* d);
	static void recWritePreorder(const TreeNode<T>* node, std::ostream&, void (*write)(std::ostream&, const T&));
	static void clear(TreeNode<T>* node);
};
#include "BST.cpp"
#endif
