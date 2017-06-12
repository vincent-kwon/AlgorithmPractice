/*
 * =====================================================================================
 *
 *       Filename:  list.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 08시 23분 52초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main() {
  list<int> l;
  
  l.push_back(100);
  l.push_back(200);
  l.push_front(0);

  list<int>::iterator itor = l.begin();
  
  for (; itor != l.end(); itor++) {
    cout << *itor << endl;
  }
  
  list<int>::iterator itor2 = find(l.begin(), l.end(), 200);

  if (itor2 == l.end()) cout << "Can't find" << endl;
  else cout << "Find !!!" << endl;

  itor2 = find(l.begin(), l.end(), 300);
  
  if (itor2 == l.end()) cout << "Can't find" << endl;
  else cout << "Find !!!" << endl;

  itor2 = max_element(l.begin(), l.end()); // memo-201706: max, min_element, all_of, none_of, any_of, binary_search, adjacent_find, for_each
  cout << "Max: " << *itor2 << endl; // nth_element, sort, merge, partition, stable_partition, is_sorted, 

  //itor2 = accumulate(l.begin(), l.end(),0); // memo-201706 : Need to how to use
  //cout << "Accu: " << *itor2 << endl;
  return 0;
}
