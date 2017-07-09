/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 09일 22시 51분 47초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

#define NUM 7

typedef struct _Node {
  struct _Node* leftChild;
  struct _Node* rightChild;
  int value;
} Node;


int parent [] = { 1, 5, 5, 2, 2, -1 , 3};
Node* nodeArray;
Node* root;

void visitDfs(Node* start) {
  if (start != NULL) {
    cout << start->value << endl;
    visitDfs(start->leftChild);
    visitDfs(start->rightChild);
  }
}

int main() {
  nodeArray = new Node[NUM];

  for (int i = 0; i < NUM; i++) {
    nodeArray[i].value = i;
    //cout << nodeArray[i].value << endl;

    // set parent
    nodeArray[parent[i]].value = parent[i];
    if (parent[i] != -1) {
      if (nodeArray[parent[i]].leftChild == NULL) {
        nodeArray[parent[i]].leftChild = &nodeArray[i]; 
      }
      else {
        nodeArray[parent[i]].rightChild = &nodeArray[i]; 
      }
    }
    else {
      root = &nodeArray[i];      
    }
  }
  
  visitDfs(root); 
  return 0;
}
