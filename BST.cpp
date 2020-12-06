#include "BST.h"

#ifndef CPSC_350_BST_CPP
#define CPSC_350_BST_CPP

#include <iostream>
#include <cstddef>

template <typename T>
BST<T>::BST() {
    root = nullptr;
    size = 0;
}
template <typename T>
BST<T>::~BST() {
    clear();
}
// Assumes value is not already in the BST
template <typename T>
void BST<T>::insertNode(const T& value) {
    TreeNode<T>*& parent = getParent(value);
    parent = new TreeNode<T>(value);
    ++size;
}
template <typename T>
bool BST<T>::searchNode(const T& value) const {

    const TreeNode<T>* current = root;
    while (current != nullptr) {
        if (value < current->key) {
            current = current->left;
        } else if (current->key < value) {
            current = current->right;
        } else {
            return true;
        }
    }
    return false;
}
template<typename T>
const T& BST<T>::getNodeValue(const T& value) const
{
    const TreeNode<T>* current = root;
    while (current != nullptr) {
        if (value < current->key) {
            current = current->left;
        }
        else if (current->key < value) {
            current = current->right;
        }
        else {
            break;
        }
    }
    return current->key;
}
template <typename T>
bool BST<T>::deleteNode(const T& value) {

    TreeNode<T>*& parent = getParent(value);
    if (parent == nullptr) {
        return false;
    }
    TreeNode<T>* temp = parent;
    if (parent->right == nullptr) {
        parent = parent->left;
        temp->left = nullptr;
    } else if (parent->right->left == nullptr) {
        parent = parent->right;
        temp->right = nullptr;
        parent->left = temp->left;
        temp->left = nullptr;
    } else {
        parent = pluckMinNode(parent->right);
        parent->left = temp->left;
        temp->left = nullptr;
        parent->right = temp->right;
        temp->right = nullptr;
    }
    delete temp;
    temp = nullptr;
    --size;
    return true;
}
template<typename T>
bool BST<T>::isEmpty() const
{
    return root == nullptr;
}
template<typename T>
size_t BST<T>::getSize() const
{
    return size;
}
template <typename T>
void BST<T>::printTree() const {
    recPrint(root);
}
template<typename T>
void BST<T>::writePreorder(std::ostream& os, void(*write)(std::ostream&, const T&)) const
{
    recWritePreorder(root, os, write);
}
template<typename T>
void BST<T>::clear()
{
    clear(root);
    root = nullptr;
    size = 0;
}
template<typename T>
TreeNode<T>*& BST<T>::getParent(const T& value)
{
    TreeNode<T>** pcurrent = &root;
    while (*pcurrent != nullptr) {
        if (value < (*pcurrent)->key) {
            pcurrent = &(*pcurrent)->left;
        }
        else if ((*pcurrent)->key < value) {
            pcurrent = &(*pcurrent)->right;
        }
        else {
            break;
        }
    }
    return *pcurrent;
}
template <typename T>
void BST<T>::recPrint(const TreeNode<T>* node) {
    if (node != NULL) {
        recPrint(node->left);
        std::cout << node->key << std::endl;
        recPrint(node->right);
    }
}
// Removes the minvalue node from the subtree with top as its root
// Assumes top != nullptr and top->left != nullptr
template<typename T>
TreeNode<T>* BST<T>::pluckMinNode(TreeNode<T>* top)
{
    while (top->left->left != nullptr) {
        top = top->left;
    }
    TreeNode<T>* temp = top->left;
    top->left = temp->right;
    temp->right = nullptr;
    return temp;
}

template<typename T>
void BST<T>::recWritePreorder(const TreeNode<T>* node, std::ostream& os, void (*write)(std::ostream&, const T&))
{
    if (node != nullptr) {
        write(os, node->key);
        recWritePreorder(node->left, os, write);
        recWritePreorder(node->right, os, write);
    }
}

template<typename T>
void BST<T>::clear(TreeNode<T>* node)
{
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}

#endif
