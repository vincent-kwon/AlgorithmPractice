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

#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class Node {
 public: 
  T value;
  virtual ~Node() {
  	cout << "Node destructor : " << value << endl;
  }
  shared_ptr<Node<T>> next;
  shared_ptr<Node<T>> prev;
};

#endif
