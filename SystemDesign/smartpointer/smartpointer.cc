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

#include <iostream>
#include <memory.h>

using namespace std;

template <typename T> 
class SmartPointer {
 public:
  T *ref;
  unsigned int *ref_count;

  SmartPointer(T* ptr) {   
    ref = ptr;
    ref_count = (T*) malloc(sizeof(unsigned int));
    *ref_count = 1;
  }

  SmartPointer(SmartPointer<T> &sptr) {
    ref = sptr.ref;
    ref_count = sptr.ref_count;
    ++(*ref_count);
  }

  virtual ~SmartPointer() {
    remove();
  }

  SmartPointer<T> & operator=(SmartPointer<T> & sptr) {
    if (this == &sptr) return *this;
    if (*ref_count > 0) remove();
    ref = sptr.ref;
    ref_count = sptr.ref_count;
    ++(*ref_count);
    return *this;
  }  

  T getValue() {
    return *ref;
  }

 protected:
  void remove() {
    --(*ref_count);
    if (*ref_count == 0) {
      cout << "ref count is now zero so auto pointer ...." << endl;
      delete ref;
      free(ref_count);
      ref = NULL;
      ref_count = NULL;
    }
  }  
};

SmartPointer<unsigned int> test() {
  unsigned int *abc = new unsigned int();
  *abc = 1000;
  SmartPointer<unsigned int> s(abc);
  return s;
}

int main() {
  SmartPointer<unsigned int> def = test(); 

  cout << "may no ref count...." << endl;
  return 0;
}
