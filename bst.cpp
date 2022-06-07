// bst.cpp
// CS24 Final Exam
// Implements class bst
// Tony Tran, 6/6/22

#include "bst.h"

#include <iostream>
using std::cout;



bst::bst(vector<int>&v){
    root = nullptr;
    for (int i= 0 ; i < v.size(); ++i){
        insert(v[i]);


    }

}

bst::~bst(){
    clear(root);


}
void bst::clear(bstNode *n){
    if(!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}


bool bst::insert(int value) {

    if (root == nullptr){
        root = new bstNode(value);
        return true;
    }else{
        return insert(value, root);
    }

    return false; 

}


bst::bstNode* bst::getSuccessorNode(int value) const{
    bstNode* starter = getNodeFor(value, root);
    if(!starter) return NULL;
    if(starter->right) { //starter has a right subtree
        bstNode *n = starter->right;
        while(n->left) n = n->left;
        return n;
    } else { // no right subtree so go up by parents till a node is a left node
        bstNode *parent = starter->parent;
        if(!starter->parent) return NULL;
        while(parent && starter == parent->right){ //till starter becomes a left node at which point p is successor
            starter = parent;
            parent = parent->parent;
        }
        return parent;
    }
}



// returns the successor value of the given value or 0 if there is none

// recursive helper for insert (assumes n is never 0)

bool bst::insert(int value, bstNode *n) {

    if(value < n->info){
        if(n->left == nullptr){
            n->left = new bstNode(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left);
        }
    } else if (value > n->info) {
        if (n->right == nullptr){
            n->right = new bstNode(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    } else {
        return false;
    }

}


void bst::deleteSubtree(int key){
    if(!getNodeFor(key,root)) return;
    bstNode *node = getNodeFor(key,root);
    clear(node);
    insert(key);

    


}
int bst::countLeaves(bstNode *n) const{
    if (!n) return 0;
    if (!n->left && !n->right){
        return 1;
    }
    else{
        return countLeaves(n->left) + countLeaves(n->right);
    }
    
}
int bst::countParentsWithTwoChildren(bstNode *n) const{
    int counter = 0;
    if (!n) return 0;
    else if(n->left && n->right){
        return countParentsWithTwoChildren(n->left)+countParentsWithTwoChildren(n->right)+1;
    }   
    else{
        return countParentsWithTwoChildren(n->left)+countParentsWithTwoChildren(n->right);
    }
}

int bst::height(bstNode *n) const{
    if(!n) return -1;
    else{
        int leftHeight = height(n->left);
        int rightHeight = height(n->right);

        if(leftHeight > rightHeight){
            return leftHeight + 1;

        }
        else{
            return rightHeight + 1;
        }
    }

    return 0;
}
void bst::outputPreOrder(bstNode *n, vector<int>& output) const{
    if(n){
        cout << n->info << " ";
        outputPreOrder(n->left,output);
        outputPreOrder(n->right,output);
    }

    return;
}
void bst::outputInOrder(bstNode *n, vector<int>& output) const{
    if (n){
        outputInOrder(n->left, output);
        cout << n->info << " ";
        outputInOrder(n->right, output);
    }

   return;
}

typename bst::bstNode* bst::getNodeFor(int value, bstNode* n) const{
    while (n != nullptr) {
        if (value == n->info) {
            return n; 
        }
        else if (value < n->info) {
            return getNodeFor(value, n->left);
        } else {
            return getNodeFor(value, n->right);
        }
    }
    return nullptr; // Node doesn't exist in tree
}
