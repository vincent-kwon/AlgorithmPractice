/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 10일 04시 56분 52초
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
// 12 15 10 11 5 6 2 3
typedef struct _Node {
  _Node* next;
  int value;
} Node;

Node* root;
Node* current;
int main() {

  Node* n = new Node();
  root = n;
  current = n;
  n->value = 12;
  
  n = new Node();
  n->value = 15;
  current->next = n;
  current = n;

  n = new Node();
  n->value = 10;
  current->next = n;
  current = n;
  
  n = new Node();
  n->value = 11;
  current->next = n;
  current = n;

  n = new Node();
  n->value = 5;
  current->next = n;
  current = n;

  n = new Node();
  n->value = 6;
  current->next = n;
  current = n;

  n = new Node();
  n->value = 2;
  current->next = n;
  current = n;

  n = new Node();
  n->value = 3;
  current->next = n;
  current = n;

  Node* tmp = root;
  Node* prevNode = NULL;

  while (tmp != NULL) {
    Node* nextNode = tmp->next;
    if (nextNode == NULL) break;

    if (nextNode->value > tmp->value) {
      if (tmp == root) {
        root = tmp->next;
      }
      else {
        prevNode->next = tmp->next;
      }
      Node* todelete = tmp;
      delete todelete;
    }
    else {
      prevNode = tmp;
    }
    tmp = nextNode;
  }

  tmp = root;

  while (tmp) {
    cout << tmp->value << " ";
    tmp = tmp->next;
  }

  return 0;
}
