/*
 * =====================================================================================
 *
 *       Filename:  friend.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 06시 43분 49초
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

class A {
  public:
    friend class B;
  private:
  int a;
};

class B {
 public:
  void print() {
    A obj;
    obj.a = 100;
    cout << obj.a << endl;
  }
};

int main() {
  B b;
  b.print();
}
