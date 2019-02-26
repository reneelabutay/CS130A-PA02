//splayTree.h

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <string>
#include <utility>

struct Node {
  int key;
  Node *parent;
  Node *left;
  Node *right;
};

class splayTree {
 public:
  //Constructor
  splayTree();

  void rightRotate(Node *oldRoot);
  void leftRotate(Node *oldRoot);
  Node* findKey(int findMe, Node *n);
  void splay(Node *current);
  

  void print();
  
  //Checks to see if item i is in the tree, prints appropriate message
  void find(int i);

  //Insert item i, prints error message if it's already in the tree
  void insert (int i);

  //Delete item i, prints error message if not contained in tree
  void remove(int i);
  
  //Search down root to look for i
  //Reaches Node x that has i
  //splays at x and returns pointer to x
  //
  //IF search reaches a NULL Node (i isn't in tree)...
  //splay the last non-null node but return NULL
  Node* access(int i);

  //Combines trees into a single tree and returns new tree
  //Access the largest key in left -> i
  //Splay so i is the root of left
  //then attach right
  Node* join(Node *T1, Node *T2);

  //Splits tree t at key i
  //call Access(i)
  //if the root has a key > i, then break the left child link from the root, return 2 subtrees
  //OR break the right child link from the root and return the 2 subtrees  
  std::pair<Node*, Node*> split(int i, Node *input);
  
 private:
  Node *rootKey;
  
};

#endif
