#ifndef CPSC_350_TREENODE_H //include guards
#define CPSC_350_TREENODE_H
template <typename T>
class TreeNode{
public:
  TreeNode(const T & k); //insert id of student or faculty
  ~TreeNode();

  T key;
  TreeNode<T> *left;
  TreeNode<T> *right;
};
template <typename T>
TreeNode<T>::TreeNode(const T& k)
    : key(k), left(nullptr), right(nullptr)
{

}
template <typename T>
TreeNode<T>::~TreeNode() {
    
}

#endif
