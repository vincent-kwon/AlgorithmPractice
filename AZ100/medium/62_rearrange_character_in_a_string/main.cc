/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 20일 20시 13분 47초
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

string str = "aaaabc"; // aaabc

int main() {
  int i;
  int j;
  char prev = str[0];
  for (i = 1; i < str.size(); i++) {
    if (prev == str[i]) {
      //find available 
      bool found = false;
      for (j = i+1; j < str.size(); j++) {
        if (str[j] != str[i]) {
          char tmp = str[j];
          str[j] = str[i];
          str[i] = tmp;
          found = true;
          break;
        }
      }
      if (!found) {
        cout << "Not possible" << endl;
        return 0;
      }
    }
    prev = str[i];
  }
  cout << "Yes: " << str  << endl;
  return 0;
}
