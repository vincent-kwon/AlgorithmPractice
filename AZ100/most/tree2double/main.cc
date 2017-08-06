/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 23일 00시 51분 51초
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
  struct Node *left;
  struct Node *right;
};

struct Link {
  int data;
  struct Link *next;
  struct Link *prev;
};

Node* newNode(int data) {
  Node* ret = new Node;
  ret->data = data;
  ret->left = NULL;
  ret->right = NULL;
  return ret;
}

Link* newLink(int data) {
  Link* ret = new Link;
  ret->data = data;
  ret->next = NULL;
  ret->prev = NULL;
  return ret;
}

void add(Link** ddHeadPtr, Link** ddTailPtr, Link* newNode) {
  if (*ddHeadPtr == NULL && *ddTailPtr == NULL) {
    *ddHeadPtr = newNode;
    *ddTailPtr = newNode;
  }
  else {
    Link* last = *ddTailPtr;
    last->next = newNode;
    newNode->prev = last;
    *ddTailPtr = newNode;
  }
}

Link* inorder(Node* root, Link** ddHeadPtr, Link** ddTailPtr) {
  if (root != NULL) {
    inorder(root->left, ddHeadPtr, ddTailPtr); // add root of left subtree
    add(ddHeadPtr, ddTailPtr, newLink(root->data));
    cout << root-> data << endl;
    inorder(root->right, ddHeadPtr, ddTailPtr); // add root of right subtree
  }
  return NULL;
}

Link *getDouble(Node* root) {
  Link *ddHead;
  Link *ddTail;
   ddHead = NULL;
   ddTail = NULL;
  inorder(root, &ddHead, &ddTail); 
  return ddHead;
}

int main() {
  Node* root = newNode(10);
  root->left = newNode(12);
  root->left->left = newNode(25);
  root->left->right = newNode(30);
  root->right = newNode(15);
  root->right->left = newNode(36);
  Link* dRoot = getDouble(root);
  Link* dHead = dRoot;
  Link* dTail;
  while(dRoot != NULL) {
    cout << dRoot->data << " ";
    dTail = dRoot;
    dRoot = dRoot->next;
  }
  cout << "" << endl;
  cout << "Now tail" << endl;
  while (dTail != NULL) {
    cout << dTail->data << " ";
    dTail = dTail->prev;
  }
  cout << "" << endl;
  return 0;
}
