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
  if(y->right) {
    y->right->parent = oldRoot;
  }
  y->right = oldRoot;
  oldRoot->parent = y;

  return;
}

void splayTree::leftRotate(Node* oldRoot) {

  Node *y = oldRoot->right;
  oldRoot->right = y->left;
  if(y->left) {
    y->left->parent = oldRoot;
  }
  y->left = oldRoot;
  oldRoot->parent = y;
  return;
}

Node* splayTree::findKey(int findMe, Node *n) {
  
  if(findMe == n->key) {
    return n;
  } else if(findMe < n->key && n->left != NULL) {
    return findKey(findMe, n->left);
  } else if(findMe > n->key && n->right != NULL) {
    return findKey(findMe, n->right);
  } else if(findMe < n->key && n->left == NULL) {
    return n;
  } else {
    return n;
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
	  current->parent = NULL;
	} else {
	  leftRotate(p);
	}
	rootKey = current;
	break;
      }
    else
      {
	if(g->left && g->left->left == current) {

	  Node *GGparent = g->parent;
	  rightRotate(g);
	  rightRotate(p);
	  
          if(g == rootKey) {
	    //grandparent is the root, so make current the new root
	    rootKey = current;
	  } else  {
	    current->parent = GGparent;
	    GGparent->left = current;
	  }
	  
	} else if(g->right && g->right->right == current) {

	  Node *GGparent = g->parent;
	  leftRotate(g);
	  leftRotate(p);

	  if(g == rootKey) {
	    rootKey = current;
	  } else {
	    current->parent = GGparent;
	    GGparent->right = current;
	  }
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
    
    p = current->parent;
    g = p->parent;
    //have to update current
  }
}

Node* splayTree::access(int i) {
  Node *splayMe = findKey(i, rootKey); //node that will be splayed

  if(rootKey != splayMe) {
    splay(splayMe);
  }
  return splayMe; //returns whatever will be the new root
  
}

std::pair<Node*, Node*> splayTree::split(int i, Node *tree) {
  Node *n = access(i); //whatever the new root is
  std::pair<Node*, Node*> twoTrees;

  if(i >= n->key) { //if i is less than root of tree
    twoTrees.first = n;
    twoTrees.second = n->right;
    n->right = NULL;

    if(twoTrees.second) {
      twoTrees.second->parent = NULL;
    }
    
  } else {//if i is greater than or equal to root of tree
    twoTrees.first = n->left;
    twoTrees.second = n;
    n->left = NULL;

    if(twoTrees.first) {
      twoTrees.first->parent = NULL;
    }
  }
  return twoTrees;
}

void splayTree::insert(int i) {
  //  std::cout<<"INSERTING "<<i<<std::endl;
  //empty tree
  if(rootKey == NULL) {
    Node *insertMe = newNode(i);
    rootKey = insertMe;
    std::cout<<"item "<<i<<" inserted"<<std::endl;
    //std::cout<<"at end of insert"<<std::endl;
    return;
  }

  std::pair<Node*, Node*> subtrees = split(i, rootKey); //splits the tree into 2 subtrees
  /*
  //tracing code
  std::cout<<"printing subtrees..."<<std::endl;
  if(subtrees.first) {
    std::cout<<"subtrees.first = "<<subtrees.first->key<<std::endl;
  } else {
    std::cout<<"subtrees.first = NULL "<<std::endl;
  }
  if(subtrees.second) {
    std::cout<<"subtrees.second = "<<subtrees.second->key<<std::endl;
  } else {
    std::cout<<"subtrees.second = NULL"<<std::endl;
  }
  std::cout<<"before if-else"<<std::endl;
  */
  //seg fault after this (in input2.txt)

  if(subtrees.first && subtrees.first->key == i) {
    //std::cout<<"in if statement"<<std::endl;
    //std::cout<<"item "<<subtrees.first->key<<" not inserted; already present"<<std::endl;
    
  } else {
    //std::cout<<"in else"<<std::endl;
    Node *insertMe = newNode(i);
    //std::cout<<"insertMe->key = "<<insertMe->key<<std::endl;
    insertMe->left = subtrees.first;
    insertMe->right = subtrees.second;
    rootKey = insertMe;

    if(subtrees.first) {
      subtrees.first->parent = insertMe;
    } if(subtrees.second) {
      subtrees.second->parent = insertMe;
    }
    std::cout<<"item "<<i<<" inserted"<<std::endl;
  }
  //std::cout<<"at end of insert"<<std::endl;
  return;
}

int splayTree::findMax(Node *n) {
  Node *current = n;
  while(current->right != NULL) {
    current = current->right;
  }
  return current->key;
}

//should return root of new JOINED tree
Node* splayTree::join(Node *T1, Node *T2) {
  Node *n;
  if(T1) {
    n = access(findMax(T1)); //will return new root of T1
    if(n->right == NULL) {
      n->right = T2;
      T2->parent = n;
    } 
  } else {
    return T2;

  }
  return n;
}

void splayTree::remove(int i) {

  Node *n = access(i); //n has the key that needs to be deleted
  
  if(n->key != i) {
    std::cout<<"item "<<i<<" not deleted; not present"<<std::endl;
  } else {

    //i is currently at root
    std::pair<Node*, Node*> children;
    children.first = n->left;
    children.second = n->right;

    delete n;
    
    rootKey = join(children.first, children.second);
    

    std::cout<<"item "<<i<<" deleted"<<std::endl;
  }
  
  return;
}

void splayTree::find(int i) {

  Node *n = access(i); //returns the new root
  if(n->key != i) {
    std::cout<<"item "<<i<<" not found"<<std::endl; 
  } else {
    std::cout<<"item "<<i<<" found"<<std::endl; 
  }
  return;
}

int splayTree::findHeight(Node *n) {
  if(n == NULL) {
    return 0;
  } else {
    
    int lheight = findHeight(n->left);
    int rheight = findHeight(n->right);

    if(lheight > rheight) {
      return (lheight+1);
    } else {
      return (rheight+1);
    }
  }
}

void splayTree::printGivenLevel(Node *root, int level) {
  if(root==NULL) {
    return;
  }
  if(level == 1) {
    std::cout<<root->key<<" ";
  } else if (level > 1) {

    printGivenLevel(root->left, level-1);
    
    printGivenLevel(root->right, level-1);

  }


}

void splayTree::print() {
  int h = findHeight(rootKey);
  for(int i = 1; i <= h; i++) {
    printGivenLevel(rootKey,i);
    std::cout<< "\n";
  }
  return;
}
