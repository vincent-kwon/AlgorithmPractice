/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 22일 18시 42분 16초
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
struct Node {
  int data;
  struct Node* left;
  struct Node* right;
};
void preOrder(Node *node) {
  if (node != NULL) {
    cout << node->data << endl;
    preOrder(node->left);
    preOrder(node->right);
  }
}
Node* newNode(int data) {
  Node* tmp = new Node;
  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;
  return tmp;
}

Node* buildUtil(int startIn, int endIn, int startPost, int endPost, int in[], int post[], int size) {
  if (size <= 0) return NULL;
  Node* n = newNode(post[endPost]);
  if (startIn >= endIn || endPost <= startPost) {
     return n;
  }
  for (int i = startIn; i <= endIn; i++) {
    if (in[i] == post[endPost]) {
       // startIn, i-1
       //  1 2
       //  2 1
       int s1 = (i-1) - startIn + 1;
       int s2 = endIn - (i+1) + 1;
       n->left = buildUtil(startIn, i-1, startPost, startPost+s1-1, in, post, s1);
       n->right = buildUtil(i+1, endIn, startPost + s1, endPost-1, in, post, s2);
       break;
    }
  }
  return n;
}

Node* buildTree(int in[], int post[], int size) {
  Node* root = buildUtil(0, size-1,0, size-1, in, post, size);
  return root;
}

int main() {
  int in[] = {4,8,2,5,1,6,3,7};
  int post[] = {8,4,5,2,6,7,3,1};
  int n = sizeof(in)/sizeof(in[0]);
  
  Node *root = buildTree(in,post,n);
  cout << "Preorder of the tree is " << endl;
  preOrder(root);
  return 0;
}
