/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 13일 06시 37분 42초
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
  struct _Node* left;
  struct _Node* right;
  int value; 
  int rank; //smaller than this
} Node;

Node* Add(Node* root, int value) {
  if (root == NULL) {
    root = new Node;
    root->value = value;
    root->rank = 0;
    root->left = root->right = NULL;
    return root;
  }
  Node* tmp = root; 
  while (tmp != NULL) {
    if (tmp->value > value) {
      if (tmp->left == NULL) {
        tmp->left = new Node;
        tmp->left->value = value;
        tmp->left->rank = 0;
        tmp->left->left = tmp->left->right = NULL;
        tmp->rank = tmp->rank + 1; // this one
        return tmp->left;
        break;
      }
      else {
        tmp->rank = tmp->rank + 1; // this one
        tmp = tmp->left;
      }
    }
    else {
      if (tmp->right == NULL) {
        tmp->right = new Node;
        tmp->right->value = value;
        tmp->right->rank = 0;
        tmp->right->left = tmp->right->right = NULL;
        return tmp->right;
        break;
        //tmp->rank = tmp->rank + 1; // this one
      }
      else {
        //tmp->rank = tmp->rank + 1; // this one
        tmp = tmp->right;
      }
    }
  }
  return NULL;
}

Node* find(Node* root, int value) {
  Node* tmp = root;
  while (tmp != NULL) {
    if ((tmp->rank + 1) == value) return tmp;
    
    else if ((tmp->rank + 1) > value) {
      tmp = tmp->left;
    }
    else {
      value = value - (tmp->rank + 1);
      tmp = tmp->right;
    }
  }
}

void traverse(Node *root) {
  Node* tmp = root;
  if (tmp != NULL) {
    cout << tmp->value << "," << tmp->rank << endl;
    traverse(tmp->left);
    traverse(tmp->right);
  }
}
int main() {
  Node* root;
  root = Add(NULL, 20);
  Add(root, 8);
  Add(root, 12);
  Add(root, 22);
  Add(root, 4);
  Add(root, 10);
  Add(root, 14);

  traverse(root);
  Node* n = find(root,1); 

  if (n != NULL)  cout << "k: " << n->value << endl;
  return 0;
}
