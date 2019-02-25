//main.cpp

#include "splayTree.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

int main () {

  std::string line;

  std::getline(std::cin,line);

  int numOps = std::stoi(line);

  splayTree tree;

  while(std::getline(std::cin,line) && numOps > 0) {
    //call print
    if(line.length() == 5) {
      tree.print();
    } else {
      
      std::string command = line.substr(0, line.find(' '));
      int key = std::stoi(line.substr(line.find(' ') + 1));

      if(command == "insert") {
	tree.insert(key);
      } else if (command == "find") {
	tree.find(key);
      } else if (command == "delete") {
	tree.remove(key);
      }
      
    }
    numOps--;
  }
  return 0;
}
