/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "TreeDB.h"
#include <iostream>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

// the default constructor, creates an empty database.
TreeDB::TreeDB() {
    this->root = nullptr;
    this->probesCount = -1;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB() {
    if(this->root == nullptr)
        return;
    deleteHelper(this->root);
    this->root = nullptr;
    this->probesCount = -1;
}

// inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry) {
    int x = 0;
    this->root = insertNode(this->root, newEntry, &x);

    return x == 0;
}


//find the largest node left of runner node
//runner is always ahead of root, root is parent of runner
//using pointer x to check if the node already exists
TreeNode* TreeDB::insertNode(TreeNode* root, DBentry* newEntry, int* x)
{

    if (root == nullptr) return new TreeNode(newEntry);
    if (root->getEntry()->getName() == newEntry->getName()) {
        *x = 5;
        return root;
    }

    if (*newEntry < *root->getEntry()) {
        root->setLeft(insertNode(root->getLeft(), newEntry,x));
    }
    else if (*newEntry > *root->getEntry()) {
        root->setRight(insertNode(root->getRight(), newEntry,x));

    } else {
        cout<<"?";
    }
    return root;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name) {
    this->probesCount = -1;
    TreeNode* found = findHelper(this->root,name);

    if(found == nullptr) {
        return nullptr;
    }
    return found->getEntry();

}

//search the tree for the key
TreeNode* TreeDB::findHelper(TreeNode* root, string name) {
    if (root == nullptr) return nullptr;
    if (root->getEntry()->getName() == name) {
        if(probesCount== -1)
            this->probesCount = 1;
        return root;
    }
    if(probesCount== -1)
        this->probesCount = 1;
    this->probesCount++;
    if (root->getEntry()->getName() < name)
        return findHelper(root->getRight(), name);

    return findHelper(root->getLeft(), name);
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name) {
    return removeHelper(nullptr,this->root, name);
}

//used to search for node to remove
//if parent == nullptr, we know runner is at this-> root!!!
//parent always follows runner
bool TreeDB::removeHelper(TreeNode* parent, TreeNode* runner, string name) {
    if (runner == nullptr) return false;
    if (runner->getEntry()->getName() < name) //name is bigger than runner entry
        return removeHelper(runner,runner->getRight(), name);
    else if(runner->getEntry()->getName() > name) //name is smaller than runner entry
        return removeHelper(runner,runner->getLeft(), name);
    else {
        bool isLeft = true; //tests which side of 
        if(parent != nullptr)
            isLeft = runner->getEntry()->getName() < parent->getEntry()->getName();
        
        if(runner->getRight() == nullptr && runner->getLeft() == nullptr) {
            //leaf node
            if(parent != nullptr) {

                if(isLeft)
                    parent->setLeft(nullptr);
                else
                    parent->setRight(nullptr);

                delete runner;
                runner = nullptr;

            } else {
                delete this->root;
                this->root = nullptr;
            }

        } else if(runner->getLeft() == nullptr) {
            //left side empty
            TreeNode* temp = runner;
            if(parent != nullptr) {
                if(isLeft) {
                    parent->setLeft(temp->getRight());
                } else {
                    parent->setRight(temp->getRight());
                }

                delete runner;
                runner = nullptr;
            } else {
                this->root = temp->getRight();
                delete runner;
                runner = nullptr;
            }
        } else if(runner->getRight() == nullptr) {
            //left side empty
            TreeNode* temp = runner;
            if(parent != nullptr) {
                if(isLeft) {
                    parent->setLeft(temp->getLeft());
                } else {
                    parent->setRight(temp->getLeft());
                }

                delete runner;
                runner = nullptr;
            } else {

                this->root = temp->getLeft();
                delete runner;
                runner = nullptr;
     
            }
        } else {

            TreeNode* biggest = findLargest(nullptr,runner->getLeft());
            TreeNode* temp = runner;
            if(parent != nullptr) {
                
                //basically checks if runner.getLeft().getRight == null; 
                //then runner.left is the biggest 
                //therefore we set root.left to null
                if(runner->getLeft() == biggest) {
                    temp->setLeft(nullptr);
                }
                if(temp->getLeft()) biggest->setLeft(temp->getLeft());
                else biggest->setLeft(nullptr);
                
                
                if(temp->getRight()) biggest->setRight(temp->getRight());
                else biggest->setRight(nullptr);
                
                if(isLeft)  parent->setLeft(biggest);
                else parent->setRight(biggest);
                
                delete runner;
                runner = nullptr;

            } else {
                TreeNode* tempRoot = this->root;
                TreeNode* temp2 = biggest;
                
                //basically checks if root.getLeft().getRight == null; 
                //then root.left is the biggest 
                //therefore we set root.left to null
                if(tempRoot->getLeft() == biggest)
                    tempRoot->setLeft(nullptr);

                biggest->setLeft(tempRoot->getLeft());
                biggest->setRight(tempRoot->getRight());
                delete this->root;
                this->root = biggest;


            }

        }


        return true;
    }

}
//find the largest node left of runner node
//runner is always ahead of root, root is parent of runner
//using pointer x to check if the node already exists
//sets root.getRight to nullptr after runner is found
TreeNode* TreeDB::findLargest(TreeNode* parent, TreeNode* runner) {
    if(runner->getRight() == nullptr) {
        if(parent) {
            if(runner->getLeft())
                parent->setRight(runner->getLeft());
            else
                parent->setRight(nullptr);
        }
        return runner;
    }
    else
        return findLargest(runner,runner->getRight());

    return nullptr;
}


// deletes all the entries in the database.
void TreeDB::clear() {
    if(this->root == nullptr)
        return;
    deleteHelper(this->root);

    this->root = nullptr;
    this->probesCount = -1;
}

//delete using depth first search
void TreeDB::deleteHelper(TreeNode* root) {

    if(root == nullptr) {
        return;
    } else {
        deleteHelper(root->getLeft());
        deleteHelper(root->getRight());
        delete root;
        root = nullptr;
    }
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    if(this->probesCount != -1)
        cout << this->probesCount << endl;
    else
        cout<< "Error: entry does not exist" <<endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const {
    if(this->root == nullptr){
        cout << 0 <<endl;
        return;
    }
    queue<TreeNode*> treequeue;
    TreeNode* tn = this->root;
    treequeue.push(tn);
    int count = 0;
    while(!treequeue.empty()) {
        tn = treequeue.front();
        treequeue.pop();
        if(tn->getEntry()->getActive()) {
            count++;
        }
        if(tn->getLeft() != nullptr) {
            treequeue.push(tn->getLeft());
        }
        if(tn->getRight() != nullptr) {
            treequeue.push(tn->getRight());
        }
    }

    cout << count << endl;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs) {
    rhs.inorder(out, rhs.root);

    return out;
}
//inorder traversal to print
void TreeDB::inorder(ostream& out, TreeNode* root) const {
    
    if(root == nullptr)
        return;
    inorder(out,root->getLeft());
    out << *root->getEntry();
    inorder(out,root->getRight());



}

