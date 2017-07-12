/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 12일 07시 18분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *  
 *   
 *       15
 *   10      20
 * 8   12  16   25
 *
 *
 * 8 10 12 15 16 20 25 => inorder traversal produces sorted array
 *
 * if  s + r > sum, then r should decrease
 * if  s + r < sum, then s should increase
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>

using namespace std;
 
typedef struct _Node {
  struct _Node *leftChild;
  struct _Node *rightChild;
  int value; 
} Node;

Node* addNode(Node* root, int i) {
  if (root == NULL) {
    root = new Node;
    root->value = i;
    return root;
  }
  
  Node *tmp = root;
  Node *result = NULL;
  while (true) {
    if (tmp->value >= i) {
      if (tmp->leftChild != NULL) {
        tmp = tmp->leftChild;
      }
      else {
        tmp->leftChild = new Node;
        tmp->leftChild->value = i;
        result = tmp->leftChild;
        break;
      } 
    }
    else {
      if (tmp->rightChild != NULL) {
        tmp = tmp->rightChild;
      }
      else {
        tmp->rightChild = new Node;
        tmp->rightChild->value = i;
        result = tmp->rightChild;
        break;
      }
    }
  }
  return result;
}

void inorderTraverse(Node* node, vector<int>& v) {
  if (node == NULL) return;
  if (node->leftChild != NULL) inorderTraverse(node->leftChild, v);
  v.push_back(node->value);
  if (node->rightChild != NULL) inorderTraverse(node->rightChild, v);
}
Node* findNode(Node* start, int num1, int num2) {
  if (start == NULL) return NULL;

  if (start->value == num1 || start->value == num2) {
    return start;  
  }
  
  Node* rLeft = findNode(start->leftChild, num1, num2);
  Node* rRight = findNode(start->rightChild, num1, num2);
  
  if (rLeft != NULL && rRight != NULL) {
    return start; 
  } 
  else if (rLeft != NULL) {
    return rLeft;
  }
  else if (rRight != NULL) {
    return rRight;
  }
  else {
    return NULL;
  }
}
int main() {
  Node* root = NULL;
  root = addNode(root, 15); // if tree is empty create a tree
  addNode(root, 10);
  addNode(root, 20);
  addNode(root, 8);
  addNode(root, 12);
  addNode(root, 16);
  addNode(root, 25);
  Node* result = findNode(root, 8, 25);
  cout << "result: " << result->value << endl;
  return 0;
}

