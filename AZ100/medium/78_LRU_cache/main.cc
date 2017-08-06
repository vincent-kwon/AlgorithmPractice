/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 07시 34분 50초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>

struct QNode
{
  struct QNode *prev, *next;
  unsigned pageNumber;
};

struct Queue
{
  unsigned count;
  unsigned numberOfFrames;
  QNode *front, *rear;
};

struct Hash
{
  int capacity;
  QNode* *array;
};

QNode* newNode(unsigned pageNUmber) {

}

Queue* createHash(int capacity) {

}

int areAllFramesFull(Queue* queue) {

}

int isQueueEmpty(Queue* queue) {

}

void deQueue(Queue* queue) 

int main() {
  Queue* q = createQueue(4);
  Hash* hash = createHash(10);

  ReferencePage(q, hash, 1);
  ReferencePage(q, hash, 2);
  ReferencePage(q, hash, 3);
  ReferencePage(q, hash, 1);
  ReferencePage(q, hash, 4);
  ReferencePage(q, hash, 5);

  cout << q->front->pageNumber << endl;
  cout << q->front->next->pageNumber << endl;
  cout << q->front->next->next->pageNumber << endl;
  cout << q->front->next->next->next->pageNumber << endl;
  return 0;
}
