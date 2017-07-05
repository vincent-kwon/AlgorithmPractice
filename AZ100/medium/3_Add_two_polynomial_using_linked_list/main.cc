/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 05일 14시 56분 32초
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
  int val;
  int expo;
  struct _Node *next;
} Node;

// TODO: Polynomial is sorted order !!!!!! 
int main() {
  Node* list1 = new Node();
  list1->val = 5;
  list1->expo = 3;
  list1->next = new Node();

  list1->next->val = 4;
  list1->next->expo = 2;
  list1->next->next = new Node();

  list1->next->next->val = 2;
  list1->next->next->expo = 0;
  list1->next->next->next = NULL;

  Node* list2 = new Node();
  list2->val = 5;
  list2->expo = 1;
  list2->next = new Node();

  list2->next->val = 5;
  list2->next->expo = 0;
  list2->next->next = new Node();

 // list2->next->next->val = 4;
 // list2->next->next->expo = 2;
  
  Node* current1 = list1;
  Node* current2 = list2;

  while (current2 != NULL) {
    if (current1 == NULL) {
      current1 = list1;
      current2 = current2->next;
    }
    else if (current1->expo == current2->expo) {
      current1->val = current1->val + current2->val;
      current1 = list1;
      current2 = current2->next;
    }
    else {
      current1 = current1->next;     
    }
  }

  current1 = list1;
  while (current1 != NULL) {
    cout << current1->val << "^" << current1->expo << " + "; 
    current1 = current1->next;
  }
  return 0;
}


