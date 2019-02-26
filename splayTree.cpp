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
  n->left = n->right = n->parent = NULL;
  return n;
}

void splayTree::rightRotate(Node* oldRoot) {
  Node *y = oldRoot->left;
  oldRoot->left = y->right;
  y->right = oldRoot;
  return;
}

void splayTree::leftRotate(Node* oldRoot) {
  Node *y = oldRoot->right;
  oldRoot->right = y->left;
  y->left = oldRoot;
  return;
}
/*
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
}*/

Node* splayTree::findKey(int findMe, Node *n) {
  std::cout<<"in findKey, n is "<<n->key<<std::endl;
  if (n == NULL && n->parent == NULL) {
    return NULL;
  } else if (n == NULL && n->parent != NULL) {
    return n->parent;
  }
  if(findMe == n->key) {
    return n;
  }
  if(findMe < n->key) {
    return findKey(findMe, n->left);
  }
  else {
    std::cout<<findMe<<" is bigger than "<<n->key<<std::endl;
    return findKey(findMe, n->right);
  }
}

void splayTree::splay(Node *current) {
  Node *p = current->parent;
  Node *g = current->parent->parent;

  while(current != rootKey) {
    if(p == rootKey)
      { //single rotation (zig or zag)
	if(p->left == current) {
	  rightRotate(p);
	} else {
	  leftRotate(p);
	}
	rootKey = current;
      }
    else
      {
	if(g->left && g->left->left == current) {
	  rightRotate(g);
	  rightRotate(p);
	  if(g == rootKey) {
	    //grandparent is the root, so make current the new root
	    rootKey = current;
	  }
	} else if(g->right && g->right->right == current) {
	  leftRotate(g);
	  leftRotate(p);
	} else if(g->left && g->left->right == current) {
	  leftRotate(p);
	  rightRotate(g);
	} else {
	  rightRotate(p);
	  leftRotate(g);
	}

	if(g == rootKey) {
	  rootKey = current;
	}
      
      }
  }
}

Node* splayTree::access(int i) {
  Node *splayMe = findKey(i, rootKey); //node that will be splayed

  splay(splayMe); //splayMe will become the new root

  return splayMe; //returns whatever will be the new root
  /*
  if(splayMe->key == i) {
    return splayMe;
  } else  {
    return NULL;
  }
*/
}

//find largest key in T1 and SPLAY IT!!

Node* splayTree::join(Node *T1, Node *T2) {
  

  return NULL;
}

std::pair<Node*, Node*> splayTree::split(int i, Node *tree) {
  std::cout<<"in split"<<std::endl;
  Node *n = access(i); //whatever the new root is
  std::pair<Node*, Node*> twoTrees;
  twoTrees.second = n->right;
  twoTrees.first = n;
  twoTrees.first->right = NULL;
  twoTrees.second->parent = NULL;

  return twoTrees;
}

void splayTree::insert(int i) {
  
  std::cout<<"inserting "<<i<<std::endl;
  //empty tree
  if(rootKey == NULL) {
    Node *insertMe = newNode(i);
    rootKey = insertMe;
    return;
  }

  std::pair<Node*, Node*> subtrees = split(i, rootKey); //splits the tree into 2 subtrees

  if(subtrees.first->key == i) {
    std::cout<<"already in tree"<<std::endl;
  } else {
    Node *insertMe = newNode(i);
    insertMe->left = subtrees.first;
    insertMe->right = subtrees.second;
    rootKey = insertMe;
    std::cout<<"item "<<i<<" inserted"<<std::endl; 
  }

  
  
  //Node *n = findKey(i, rootKey);
  /*
  std::cout<<n->key<<" is n"<<std::endl;
  if(n->key == i) {
    //key was found in tree
    std::cout<<"item "<<i<<" not inserted; already present"<<std::endl;
  } else {
    //key not in tree, insert it here

    std::pair<Node*, Node*> subtrees = split(i, rootKey); //splits the tree into 2 subtrees

    Node *insertMe = newNode(i);

    insertMe->left = subtrees.first;
    insertMe->right = subtrees.second;

    rootKey = insertMe;
    
    std::cout<<"item "<<i<<" inserted"<<std::endl;
  }*/
  
  return;
}


void splayTree::remove(int i) {
  std::cout<<"in remove"<<std::endl;
  return;
}

void splayTree::find(int i) {
  std::cout<<"in find"<<std::endl;

  Node *n = access(i); //returns the new root
  if(n->key != i) {
    std::cout<<"item "<<i<<" not found."<<std::endl; 
  } else {
    std::cout<<"item "<<i<<" found."<<std::endl; 
  }
  return;
}

void splayTree::print() {
  std::cout<<"printing"<<std::endl;
  return;
}
