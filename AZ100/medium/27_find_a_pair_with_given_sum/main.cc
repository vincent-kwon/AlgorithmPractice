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
 * Memo: it is about finding two elements in sorted array.
 *       what about "N" number to form some value? 
 *       Dynamic programming can be easiy solve
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

int main() {
  Node* root = NULL;
  root = addNode(root, 15); // if tree is empty create a tree
  addNode(root, 10);
  addNode(root, 20);
  addNode(root, 8);
  addNode(root, 12);
  addNode(root, 16);
  addNode(root, 25);
  vector<int> v;
  inorderTraverse(root, v);
  for (int i : v) {
    cout << i << " ";
  }
  cout << "" << endl;

  int start = 0; 
  int end = v.size()-1;
  int sum = 33;
  while (start < end) {
    if ((v[start] + v[end]) > sum) {
      end--;
    }
    else if ((v[start] + v[end]) < sum) {
      start++;
    }
    else {
      cout << "Found : " << v[start] << "," << v[end] << endl;
      break;
    }
  }
  cout << "Not found: " << endl;
  return 0;
}

