/*
 * =====================================================================================
 *
 *       Filename:  vclist.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 13일 15시 02분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdexcept>
#include "vclist.h"

using namespace std;

template <typename T>
vclist<T>::vclist() : head(NULL), tail(NULL), count(0) {

}

template <typename T>
vclist<T>::~vclist() {

}

template <typename T>
void vclist<T>::push_front(T i) {
  count++;
  Node<T>* n = new Node<T>();
  n->value = i;
  if (head == NULL) {
    n->next = NULL;
    n->prev = NULL;
    head = tail = n;
  }

  else {
    n->next = head;
    n->prev = NULL;
    head->prev = n;
    head = n;  
  }
}

template <typename T>
void vclist<T>::push_back(T i) {
  count++;
  Node<T>* n = new Node<T>();
  n->value = i;
  if (tail == NULL) {
    n->next = NULL;
    n->prev = NULL;
    head = tail = n;
  }

  else {
    n->prev = tail;
    n->next = NULL;
    tail->next = n;
    tail = n;
  }
}

template <typename T>
void vclist<T>::pop_front() {
  if (head == NULL) { // nothing to return;
     return;
  }
  else {
    count--;
    Node<T>* tmp = head->next;
    if (tmp == NULL) {
      head = tail = NULL;
    }
    else {
      head = tmp;
      head->prev = NULL;
    }
  }
}

template <typename T>
void vclist<T>::pop_back() {
  if (tail == NULL) {
    return;
  }
  else {
    count--;
    Node<T>* tmp = tail->prev;
    if (tmp == NULL) {
      head = tail = NULL;
    }
    else {
      tmp->next = NULL;
      tail = tmp;
    }
  }
}

template <typename T>
T vclist<T>::front() {
  if (head != NULL) return head->value;
  else throw underflow_error("no element"); 
}

template <typename T>
T vclist<T>::back() {
  if (tail != NULL) return tail->value;
  else throw underflow_error("no element");
}

template <typename T>
Iterator<Node<T>> vclist<T>::begin() {
  Iterator<Node<T>> itor(head, tail);
  return itor;
}

template <typename T>
Iterator<Node<T>> vclist<T>::end() {
  Iterator<Node<T>> itor(head, tail);
  itor.pos = tail + 1;
  return itor;
}

template <typename T>
void vclist<T>::insert(T i) {

}

template <typename T>
void vclist<T>::erase(T i) {

}

template <typename T>
int vclist<T>::size() {
  return count;
}

template <typename T>
bool vclist<T>::find(T i) {
  return true;
} 

int main() {
  vclist<int> l;
  l.push_front(100);
  l.push_front(200);
  l.push_front(300);
  l.push_back(1000);
  l.push_back(2000);
  Iterator<Node<int>> itor = l.begin();
//  for (itor; itor != l.end(); itor++) {
//    cout << *itor << endl;
//  }
  l.pop_front();
  l.pop_back();
  l.pop_back();
  l.pop_front();
  cout << l.front() << endl;
  cout << l.back() << endl;
  cout << l.size() << endl;
  return 0;
}
