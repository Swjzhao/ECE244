#include "TreeNode.h"   
// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr){
    this->left = nullptr;
    this->right = nullptr;
    this->entryPtr = _entryPtr;
}

    // the destructor
TreeNode::~TreeNode(){
    delete entryPtr;
    this->entryPtr = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

    // sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    this->left = newLeft;
}

    // sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
   this->right = newRight; 
}

    // gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return this->left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return this->right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const{
    return this->entryPtr;
}