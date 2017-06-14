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

#ifndef __vclist_h__
#define __vclist_h__
#include <iostream>
#include "iterator.h"

using namespace std;

template <typename T>
class Node {
 public: 
  T value;
  Node<T>* next;
  Node<T>* prev;
};

template <typename T>
class vclist {
 public:
  vclist();
  virtual ~vclist();
  virtual void push_front(T t);
  virtual void push_back(T t);
  virtual void pop_front();
  virtual void pop_back();
  virtual T front();
  virtual T back();
  Iterator<Node<T>> begin();
  Iterator<Node<T>> end();
  virtual void insert(T t);
  virtual void erase(T t);
  virtual int size();
  virtual bool find(T t);
  // top
  // add (lambda enabled)
  // subclassing vclist so it can add top, add, and disable front (is it possible??? polymophism) 
  // iterator
  Node<T>* head;
  Node<T>* tail;
  //Node<T>** itorator;
  int count;
 private:
  // prohibit copy constructor
  // vclist(const T& obj); Todo
  // do not delete???? memo-201706
};

#endif
