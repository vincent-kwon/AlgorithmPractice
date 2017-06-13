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
#include "vclist.h"

using namespace std;

template <typename T>
vclist<T>::vclist() : head(NULL), tail(NULL) {

}

template <typename T>
vclist<T>::~vclist() {

}

template <typename T>
void vclist<T>::push_front(T i) {
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
  Node<T>* n = new Node<T>();
  n->value = i;
  if (tail == NULL) {
    n->next = NULL;
    n->prev = NULL;
    head = tail = n;
  }

  else {
    n->next = tail;
    n->prev = tail->prev;
    head->prev = n;
    tail = n;  
  }
}

template <typename T>
void vclist<T>::pop_front() {

}

template <typename T>
void vclist<T>::pop_back() {

}

template <typename T>
T vclist<T>::front() {
  return head->value;
}

template <typename T>
T vclist<T>::back() {
  return tail->value;
}

template <typename T>
void vclist<T>::begin() {

}

template <typename T>
void vclist<T>::end() {

}

template <typename T>
void vclist<T>::insert(T i) {

}

template <typename T>
void vclist<T>::erase(T i) {

}

template <typename T>
int vclist<T>::size() {
  return 0;
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
  cout << l.front() << endl;
  cout << l.back() << endl;
  return 0;
}
