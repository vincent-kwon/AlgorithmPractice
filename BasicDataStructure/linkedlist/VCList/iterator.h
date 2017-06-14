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

using namespace std;

template <typename T>
class Iterator {
 public:
  Iterator(T* h, T* t);
  virtual ~Iterator();
//  T& operator+(int offset);
//  bool operator==(const T& rhs);
//  bool operator!=(const T& rhs);
//  bool operator*();
  T* head;
  T* tail;
  T* pos;
 private:
};
