//splayTree.cpp

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "splayTree.h"

//Constructor
splayTree::splayTree() {
  this->rootKey = NULL;
}

Node* newNode(int i) {
  Node *n = new Node;
  n->key = i;
  n->left = n->right = NULL;
  return n;
}

Node* splayTree::rightRotate(struct Node* oldRoot) {
  Node *y = oldRoot->left;
  oldRoot->left = y->right;
  y->right = oldRoot;
  return y;
}

Node* splayTree::leftRotate(struct Node* oldRoot) {
  Node *y = oldRoot->right;
  oldRoot->right = y->left;
  y->left = x;
  return y;
}

Node* splayTree::splay(Node* root, int key) {
  if(root == NULL || root->key == key) {
    return root;
  }
  //traverse down left subtree
  if(key < root->key){
    if(root->left == NULL) {
      return root;
    }
    //go on left child's left subtree
    if(root->left->key > key) {
      root->left->left = splay(root->left->left, key);
      root = rightRotate(root);

      //go down left child's right tree
    } else if (root->left->key < key) {
      root->left->right = splay(root->left->right, key);
      if(root->left->right != NULL) {
	root->left = leftRotate(root->left);
      }
    }
    return rightRotate(root); //could be wrong
  }
  
  else if (key > root->key) {
      
    if(root->right == NULL) {
      return root;
    }

    if(root->right->key > key) {
      root->right->left = splay(root->right->left, key);

      if(root->right->left != NULL) {
	root->right = rightRotate(root->right);
      }
      
    }} else if(root->right->key < key) { //zag-zag
      root->right->right = splay(root->right->right, key);
      root = leftRotate(root);
    }
    return leftRotate(root); //could be wrong
  }
}

Node* splayTree::access(int i) {
  return splay(this->rootKey, i);
}

void splayTree::insert(int i) {
  std::cout<<"in insert"<<std::endl;
  return;
}

void splayTree::remove(int i) {
  std::cout<<"in remove"<<std::endl;
  return;
}

void splayTree::find(int i) {
  std::cout<<"in find"<<std::endl;
  return;
}

void splayTree::print() {
  std::cout<<"printing"<<std::endl;
  return;
}
