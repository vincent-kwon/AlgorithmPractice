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
 *        Company:  Tamsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include "iterator.h"
#include <stdexcept>

using namespace std;

template <typename T>
Iterator<T>::Iterator(Node<T>* h) : head(h), pos(h) {
  
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
  if (pos != NULL) {
	  pos = pos->next;
  }
  else {
  	throw underflow_error("no more possible");
  }
  return *this;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& rhs) {
  if (pos == rhs.pos) return true;
  else return false;
}
// need to define equal here

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) {
  if (pos == rhs.pos) return false;
  else return true;
}

template <typename T>
T Iterator<T>::operator*() {
  return (pos->value);
}

template <typename T>
Iterator<T>:: ~Iterator() {
  cout << "Destructor" << endl;
}

template class Iterator<int>;
