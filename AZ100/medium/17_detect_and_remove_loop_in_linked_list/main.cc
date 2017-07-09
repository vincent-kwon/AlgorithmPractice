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

  Node* startLoop = n;

  n = new Node();
  n->value = 2;
  current->next = n;
  current = n;

  n = new Node();
  n->value = 3;
  current->next = n;
  current = n;

  n->next = startLoop;

  Node* slower = root;
  if (root == NULL) return 0;

  Node* faster = root->next;
  bool hasLoop = false;
  while (true) {
    if (faster == NULL || slower == NULL) {
      break;
    }
    if (faster == slower) {
      hasLoop = true; 
      break;
    }
    slower = slower->next;
    faster = faster->next;
    if (faster != NULL) faster = faster->next;
  }
  cout << "Detect Loop : " << hasLoop << endl;

  faster = root;
  slower = root;

  while (true) {
    slower = slower->next;
    faster = faster->next->next;

    if (faster == slower) break;
  }

  Node* restart = root;

  while (true) {
    if (restart == slower) break;
    slower = slower->next;
    restart = restart->next;
  }

  Node* tmp = root; 
  while (true) {
    cout << tmp->value << endl;
    if (tmp == restart) {
      break;
    }
    tmp = tmp->next;
  }
  return 0;
}
