/*
 * =====================================================================================
 *
 *       Filename:  class_template.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 03시 34분 20초
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

#ifndef __simple_h__
#define __simple_h__

class Simple {
 public:
  Simple();
  virtual ~Simple();
  virtual void publicMethod();
  Simple& operator=(const Simple& rhs);
  static const int mConstantInt = 2; // revisit
  static int sStaticInt;
 protected:
  int mProtectedInteger;
 private:
  Simple(const Simple&src);
};

#endif

Simple::Simple() {
  cout << "Const Simiple" << endl;
}

Simple::~Simple() {
  cout << "Destroy Simple" << endl;
}

void Simple::publicMethod() {
  cout << "Public method" << endl;
}

Simple& Simple::operator=(const Simple& rhs) {
  return *this; // revisit: = should return *this
}

int main() {
  Simple s;
  s.publicMethod();
  // Simple::sStaticInt = 777; // memo_201706 : why static failed???
  // cout << Simple::sStaticInt << endl;
  return 0;
}
