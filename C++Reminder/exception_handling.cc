/*
 * =====================================================================================
 *
 *       Filename:  exception_handling.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 02시 21분 24초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <exception>
#include <stdexcept> // last_visit: standard exception

using namespace std;

class MyException2 : public runtime_error {
  virtual const char* what(const string& msg) const noexcept { // last_visit: vcc what cn
    string s = "FUCK";
    return s.c_str();
  }
}

class MyException : public runtime_error {
 // memo_201706: invalid_argument, bad_alloc, bad_cast, out_of_range, overflow_error, underflow_error
 public: 
  MyException(const string& str) : runtime_error(str.c_str()), _str(str) {
  };
  virtual const char* what() const noexcept { // memo_201706
    return _str.c_str();
  }
 private:
  string _str;
};

int main() {
  try {
    throw MyException( "vincent" );
  } catch (const MyException& m) { // memo_201706
    cout << m.what() << endl;
    throw (bad_alloc()) ;
  } 
  return 0;
}
