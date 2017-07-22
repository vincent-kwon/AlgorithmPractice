/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 21일 10시 05분 41초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 * 
 * Traverse is can't traverse one by one
 *
 * Go left-most first
 *
 *
 * =====================================================================================
 */

#include <iostream>
//#include <memory.h>
//#include <unistd.h>
#include <stdlib.h> // memo: malloc

using namespace std;

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct sNode {
  struct Node *t;
  struct sNode *next;
};

void push(sNode **s, Node *k) {
  struct sNode *tmp = (struct sNode *)malloc(sizeof(struct sNode));

  tmp->t = k;
  tmp->next = *s;
  (*s) = tmp;
}

struct Node *pop(struct sNode **s) {
  struct Node *t;
  struct sNode *st;
  st = *s;
  (*s) = (*s)->next;
  t = st->t;
  free(st);
  return t;
}

int isEmpty(struct sNode *s) {
  if (s == NULL) return 1;
  return 0;
}

struct Node* newNode (int data) {
#if 0
  struct Node *temp = new struct Node;
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
#else 
  Node *temp = new Node; // struct can be new
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
#endif
}

void inorder(struct Node *root) {
  if (root != NULL) {
    inorder(root->left);
    cout << "VC: " << root->data << endl;
    inorder(root->right);
  }
}

void merge(struct Node *root1, struct Node *root2) {
  struct sNode *s1 = NULL;
  struct Node *current1 = root1;
  struct sNode *s2 = NULL;
  struct Node *current2 = root2;

  if (root1 == NULL) {
    inorder(root2);
    return;
  }

  if (root2 == NULL) {
    inorder(root1);
    return;
  }
#if 0
  while (current1 != NULL || !isEmpty(s1) || current2 != NULL || !isEmpty(s2)) {
    if (current1 != NULL || current2 != NULL) {
      if (current1 != NULL) {
        push(&s1, current1);  
        current1 = current1->left;
      }
      if (current2 != NULL) {
        push(&s2, current2);
        current2 = current2->left;
      }
    }
    else {
      if (isEmpty(s1)) {
        while(!isEmpty(s2)) {
          current2 = pop(&s2);
          current2->left = NULL;
          inorder(current2);
          return;
        }
      }
      if (isEmpty(s2)) {
        while(!isEmpty(s1)) {
          current1 = pop(&s1);
          current1->left = NULL;
          inorder(current1);
          return;
        }
      }
      current1 = pop(&s1);
      current2 = pop(&s2);

      if (current1->data < current2->data) {
        cout << current1->data << endl;
        current1 = current1->right; 
        push(&s2, current2);
        current2 = NULL;
      }
      else {
        cout << current2->data << endl;
        current2 = current2->right;
        push(&s1, current1);
        current1 = NULL;
      }
    }
  }
  #else
  while (current1 != NULL || current2 != NULL || !isEmpty(s1) || !isEmpty(s2)) {
    if (current1 != NULL || current2 != NULL) {
      if (current1 != NULL) {
        push(&s1, current1); // s1 is sNode* this can be rewritten as s1->
        current1 = current1->left;
      }
      if (current2 != NULL) {
        push(&s2, current2);
        current2 = current2->left;
      }
    }
    else {
      // inorder principal is kept
      // if current1 is empty and s1 is empty, then nothing left to s1
      if (isEmpty(s1)) {
        while (!isEmpty(s2)) {
          current2 = pop(&s2);
          current2->left = NULL;
          inorder(current2);
          return;
        }
        // need to only take care of current2 and others
      }
      if (isEmpty(s2)) {
        while (!isEmpty(s1)) {
          current1 = pop(&s1);
          current1->left = NULL;
          inorder(current1);
          return;
        }
      }
      
      current1 = pop(&s1);
      current2 = pop(&s2);

      if (current1->data < current2->data) {
        cout << "VC: " << current1->data << endl;
        current1 = current1->right;
        push(&s2, current2);
        current2 = NULL;
      }    
      else {
        cout << "VC: " << current2->data << endl;
        current2 = current2->right;
        push(&s1, current1);
        current1 = NULL;
      }
    }
  }
  #endif
}

int main() {
  struct Node *root1 = NULL;
  struct Node *root2 = NULL;

  root1 = newNode(3);
  root1->left = newNode(1);
  root1->right = newNode(5);

  root2 = newNode(4);
  root2->left = newNode(2);
  root2->right = newNode(6);

  merge(root1, root2);  
  return 0;
}
