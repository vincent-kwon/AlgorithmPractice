/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 17일 23시 44분 46초
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

typedef struct _Node {
  int value;
  struct _Node *left;
  struct _Node *right;
} Node;

void insert(Node* root, int value, bool leftChild) {
  if (root == NULL) {
    root = new Node;
    root->left = NULL;
    root->right = NULL;
    root->value = value;
    return;
  }
  if (leftChild) {
    root->left = new Node;
    root->left->left = root->left->right = NULL;
    root->left->value = value;
    return;
  }
  else {
    root->right= new Node;
    root->right->left = root->right->right = NULL;
    root->right->value = value; 
    return;
  }
} 

int main() {
  
  return 0;
}
