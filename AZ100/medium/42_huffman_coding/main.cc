/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 18일 21시 20분 11초
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

// Question
// 
// a 5
// b 9
// c 12
// d 13
// e 16
// f 45
//
//        100
// 45              55
//             25                    30
//         12     13             14      16
//                            5      9  
//           1
//    2             3 
//  4  5        6      7
// 8 9 10 11  12 13  14 15

#define MAX_VALUE 6 

int array[6] = { 
 5, 9, 12, 13, 16, 45
};

char alpha[6] = {
 'a','b','c','d','e','f'
};

typedef struct _Node {
  int value;
  char a;
  struct _Node *left;
  struct _Node *right;
} Node;

Node heap[6]; 

int lastIndex;

Node* cloneMin() {
  Node *newNode = new Node;
#if 0
  newNode->value = heap[0].value;
  newNode->a = heap[0].a;
  newNode->left = heap[0].left;
  newNode->right = heap[0].right;
#endif
  *newNode = heap[0];
  return newNode;
}

void swap(int first, int second) {
#if 0
  Node tmp;

  tmp.value = heap[first].value;
  tmp.a = heap[first].a;
  tmp.left = heap[first].left;
  tmp.right = heap[first].right;

  heap[first].value = heap[second].value;
  heap[first].a = heap[second].a;
  heap[first].left = heap[second].left;
  heap[first].right = heap[second].right;

  heap[second].value = tmp.value;
  heap[second].a = tmp.a;
  heap[second].left = tmp.left;
  heap[second].right = tmp.right;
#else
  Node tmp = heap[first];
  heap[first] = heap[second];
  heap[second] = tmp;
#endif
}
void insertNode(Node* node) {
  lastIndex++;
  int tmp = lastIndex;
  heap[tmp].value = node->value;
  heap[tmp].left = node->left;
  heap[tmp].right = node->right; 
  while (tmp >= 0) {
    int parentIndex = -1;
    // get parent
    if (tmp == 0) {
      // 0 can't have parent
      break;
    }
    else {
      if (tmp % 2 == 0) {
        parentIndex = tmp / 2 - 1;
      }
      else {
        parentIndex = tmp / 2;
      }
    } 
    if (heap[parentIndex].value > heap[tmp].value) {
      swap(parentIndex, tmp);
      tmp = parentIndex;
    }
    else break;
  }  
}

void popMin() {
  // swap first and last
  swap(0, lastIndex);
  // reduce last index
  lastIndex--;

  // if bigger than smaller, then swap until tmpIndex <= lastIndex
  int tmp = 0;
  
  while (tmp <= lastIndex) {
    int leftIndex = tmp * 2 + 1;
    int rightIndex = tmp * 2 + 2;

    int bigger;
    int smaller;

    if (leftIndex > lastIndex) break;
    else if (leftIndex == lastIndex) smaller = leftIndex;
    else {
      if (heap[leftIndex].value < heap[rightIndex].value) {
        bigger = rightIndex;
        smaller = leftIndex;
      } 
      else {
        bigger = leftIndex;
        smaller = rightIndex;
      }
    }  
    if (heap[tmp].value > heap[smaller].value) {
      swap(tmp, smaller);
      tmp = smaller;
    }
    else break;
  }
}

Node *root = NULL;

void traverse(Node *root, string str) {
  Node* tmp = root;
  if (tmp == NULL) return;
  else {
    traverse(tmp->left, str+"0");
    traverse(tmp->right, str+"1");
    if (tmp->left == NULL && tmp->right == NULL) cout << "[leaf] value: " << tmp->value << ", char: " << tmp->a << ", code:" << str << endl;
  }
}

int main() {
  for (int i = 0; i < MAX_VALUE; i++) {
    heap[i].value = array[i]; 
    heap[i].a = alpha[i];
    heap[i].left = NULL;
    heap[i].right = NULL;
    lastIndex = i;
  }
  
  while (lastIndex > 0) {
    //remove top
    Node* smaller = cloneMin();
    popMin();
    Node* bigger = cloneMin();
    popMin();

    //new sumation
    Node *newNode = new Node;
    root = newNode;
    newNode->value = smaller->value + bigger->value;
    newNode->left = smaller;
    newNode->right = bigger;
    //cout << "NewNode: " << newNode->value << ", left: " << newNode->left->value << ", rigt: " << newNode->right->value << endl;
    insertNode(newNode); // heapify
  }
  
  traverse(root,"");
  return 0;
}
