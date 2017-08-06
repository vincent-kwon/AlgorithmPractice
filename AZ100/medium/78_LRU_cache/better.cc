/*
 * =====================================================================================
 *
 *       Filename:  better.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 19시 51분 54초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>

using namespace std;
// why queue? yes
// why hash? 

struct Node {
  struct Node* prev;
  struct Node* next;
  unsigned int address;  // 32 bit address
};

struct DList {
  struct Node* head;
  struct Node* tail;
  int capacity;
  int current;
};

struct CHash {
  int bucketSize;
  struct Node* *array;
};

bool isDListFull(DList& dlist) {
  return (dlist.capacity > dlist.current)? false: true;
}

Node* dequeueDList(DList& dlist) {
  // remove from dlist (assume not single one) 
  Node* tmp = dlist.tail;
  Node* prev = tmp->prev;
  prev->next = NULL;
  dlist.tail = prev;
  dlist.current--;
  return tmp;
}

bool isDListEmpty(DList& dlist) {
  return (dlist.current == 0)? true: false;
}

Node* isCached(CHash &chash, int address) {
  int bucket = address % 7;
  Node* tmp = chash.array[bucket];
  while (tmp) {
    if (tmp->address == address) return tmp;
    else tmp = tmp->next;
  }
  return NULL;
}

void addToCHash(CHash& chash, Node* node) {
  int bucket = node->address % 7;
  Node* tmp = chash.array[bucket];
  while (tmp) {
    if (tmp->next == NULL) {
      tmp->next = node;
      break;
    }
    else {
      tmp = tmp->next;
    }
  }
}

void addToDList(DList& dlist, Node* node) {
  if (isDListEmpty(dlist)) {
    dlist.tail = node;
    dlist.head = node;
    cout << "dlist add: " << node->address << "," << dlist.current + 1<< endl;
  }
  else {
    cout << "dlist is not empty " << dlist.current << endl;
    Node* current = dlist.head;
    current->prev = node;
    node->next = current;
    dlist.head = node;
  }
  dlist.current += 1;
}

void referPage(CHash& chash, DList& dlist, int address) {
  Node* tmp = isCached(chash, address);
  if (tmp) {
    if (dlist.head == tmp && dlist.tail == tmp) return;
    else if (dlist.head == tmp) return;
    else if (dlist.tail == tmp) {
      // remove from tail
      Node* prevNode = tmp->prev;
      prevNode->next = NULL;
      dlist.tail = prevNode;
    }
    else {
      Node* prevNode = tmp->prev;
      Node* nextNode = tmp->next;
      prevNode->next = nextNode;
      nextNode->prev = prevNode;
    }
    addToDList(dlist, tmp);
  }
  else {
    // check full, if true, dequeue one
    if (isDListFull(dlist)) {
      Node* oneDequeued = dequeueDList(dlist);
      cout << "dlist full " << endl;
      // TODO: Remove from hash 
    }
  
    Node* newNode = new Node;
    newNode->address = address;
    newNode->prev = NULL;
    newNode->next = NULL;
    addToCHash(chash, newNode);
    cout << "going to add " << newNode->address << endl;
    addToDList(dlist, newNode);
  }
}

void printDList(DList& dlist) {
  Node* tmp = dlist.head;
  while (tmp) {
    cout << tmp->address << " ";
    tmp = tmp->next;
  }
  cout << " " << endl;
}

int main() {
  DList dlist;
  dlist.capacity = 3;
  dlist.current = 0; // memo: do not forget initialization
  dlist.head = NULL;
  dlist.tail = NULL;

  CHash chash;
  chash.bucketSize = 7;
  chash.array = new Node*[7];
  
  referPage(chash, dlist, 10); // 3
  referPage(chash, dlist, 22); // 1
  referPage(chash, dlist, 26); // 6
  referPage(chash, dlist, 21); // 0
  referPage(chash, dlist, 29); // 1
  referPage(chash, dlist, 38); // 3

  printDList(dlist);
  return 0;
}
