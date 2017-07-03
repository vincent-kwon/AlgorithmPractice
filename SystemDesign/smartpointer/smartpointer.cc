/*
 * =====================================================================================
 *
 *       Filename:  smartpointer.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 03일 07시 55분 21초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

// TODO: -> for object pointer
//       * to get value

#include <iostream>
#include <memory.h>
#include <mutex>

using namespace std;

template <typename T> 
class SmartPointer {
 public:
  T *ref;
  unsigned int  *ref_count;

  SmartPointer(T* ptr) {   
    ref = ptr;
    ref_count = (unsigned int*) malloc(sizeof(unsigned int));
    m = new mutex;
    unique_lock<mutex> ul(*m);
    *ref_count = 1;
    ul.unlock();
    cout << "Init ref count to " << *ref_count << endl;
  }

  SmartPointer(SmartPointer<T> &sptr) {
    ref = sptr.ref;
    ref_count = sptr.ref_count; // when move, new smart pointer should share pointer to ref_count , not value;
    m = sptr.m;
    unique_lock<mutex> ul(*m);
    ++(*ref_count); // TODO: do we need to add "lock protection" ?? 
    ul.unlock();
    cout << "now ref count is " << *ref_count << endl;
  }

  virtual ~SmartPointer() {
    remove();
  }

  SmartPointer<T> & operator=(SmartPointer<T> & sptr) {
    if (this == &sptr) return *this;
    if (*ref_count > 0) remove();
    ref = sptr.ref;
    ref_count = sptr.ref_count;
    m = sptr.m;
    unique_lock<mutex> ul(*m);
    ++(*ref_count);
    return *this;
  }  
  
  T operator*() {
    getValue();
  }

  T* operator->() {
    return ref;
  }

  T getValue() {
    return *ref;
  }

 protected:
  mutex* m;
  void remove() {
    unique_lock<mutex> ul(*m);
    if (ref_count == NULL) return;
    --(*ref_count);
    if (*ref_count == 0) {
      //T t = *ref;
      //cout << "t: " << t << "," << *t << endl;
      delete ref;
      free(ref_count);
      ref = NULL;
      ref_count = NULL;
    }
    else {
      cout << "ref count is non-zero :" << *ref_count << endl;
    }
    ul.unlock();
  }  
};

int main() {
  unsigned int* i = new unsigned int;
  struct St {
    int a;
    int b;
  };

  struct St* st =  new struct St;
  st->a = 7;
  st->b = 7000;
  
  SmartPointer<struct St> sss(st);
  cout << "SSS->b:" << sss->b << endl;

  *i = 1000;
  SmartPointer<unsigned int> def(i); 
  SmartPointer<unsigned int> abc(def);  
  cout << "print abc: " << *abc << endl;
  return 0;
}
