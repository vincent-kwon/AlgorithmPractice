/*
 * =====================================================================================
 *
 *       Filename:  iterator.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 14일 08시 25분 36초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include "iterator.h"

using namespace std;

template <typename S>
Iterator<S>::Iterator(Node<S>* h, Node<S>* t) : head(h->head), pos(h->pos), tail(h->tail) {
  
}

template <typename S>
Iterator<Node<S>>& Iterator<S>::operator+(int offset) {
  pos = pos + offset;
  return *this;
}

template <typename S>
bool Iterator<S>::operator==(const S& rhs) {
  if (pos == rhs.pos) return true;
  else return false;
}
// need to define equal here

template <typename S>
bool Iterator<S>::operator!=(const S& rhs) {
  if (pos <= rhs.tail) return false;
  else return true;
}

template <typename S>
S Iterator<S>::operator*() {
  return (pos->value);
}

template <typename S>
Iterator<T>:: ~Iterator() {

}

