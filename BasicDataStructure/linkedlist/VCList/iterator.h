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

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
class Iterator {
 public:
  Iterator(shared_ptr<Node<T>> h);
  virtual ~Iterator();
  Iterator<T>& operator++();
  bool operator==(const Iterator<T>& rhs);
  bool operator!=(const Iterator<T>& rhs);
  T operator*();
  shared_ptr<Node<T>> head;
  shared_ptr<Node<T>> pos;
 private:
};

#endif
