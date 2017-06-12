/*
 * =====================================================================================
 *
 *       Filename:  map.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 09시 05분 12초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>

using namespace std;

int main() {
  map<string, int> mm;

  mm["abc"] = 1;
  mm["def"]= 2;

  cout << mm["abc"] << endl;
  cout << mm["def"] << endl;
  
  auto iter = mm.find("abc"); // memo-201706 : find from map
  if (iter != mm.end()) cout << iter->second << endl;

  mm.erase("abc");

  iter = mm.find("abc");  
  if (iter != mm.end()) cout << iter->second << endl; // memo-201706 : iter remain old so watch out
  else cout << " Not found " << endl;

  mm.insert(make_pair("ghi", 1000));

  cout << mm["ghi"] << endl;
  return 0;
}
