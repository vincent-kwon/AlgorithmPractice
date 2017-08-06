/*
 * =====================================================================================
 *
 *       Filename:  class_template.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 04시 28분 20초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <sstring> 

using namespace std;

template<typename T>
class SimpleData2 {
 public: 
  SimpleData(T&inObject);
 protected:
};

template<typename T>
class SimpleTemplate {
 public:
  SimpleTemplate(T& inObject);
  const T& get() const;
  void set(T& inObject);
 protected:
  T& mObject;
};

template<typename T>
SimpleTemplate<T>::SimpleTemplate(T& inObject) : mObject(inObject) 
{

}

template<typename T>
const T& SimpleTemplate<T>::get() const 
{
  return mObject;
}

template<typename T> // memo_201706 : add a class and all methods definitions
void SimpleTemplate<T>::set(T& inObject) 
{
  mObject = inObject;
}

int main() {
  int i = 7;
  SimpleTemplate<int> intWrapper(i);
  i = 2;
  cout << intWrapper.get() << endl;;
  string s = "ABC";
  SimpleTemplate<string> stringWrapper(s);
  cout << stringWrapper.get() << endl;
}
