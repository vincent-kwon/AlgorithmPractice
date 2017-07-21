/*
 * =====================================================================================
 *
 *       Filename:  better.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 20일 20시 31분 01초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue> 

using namespace std;

const int MAX_CHAR = 26;

struct Key {
  int freq;
  char ch;
 
  bool operator<(const Key &k) const { // memo: const 
    return freq < k.freq;
  }
};

void rearrangeString(string str) {
  int n = str.size();
  int count[MAX_CHAR]  = {0, };

  for (int i = 0; i  < n ; i++) 
    count[str[i]-'a']++;

  priority_queue<Key> pq;
  for (char c = 'a'; c <= 'z'; c++) {
    if (count[c-'a']) pq.push(Key {count[c-'a'], c}); // memo: Key { ... } anonymous structure defining
  }
  str = "";

  Key prev {-1, '#'};

  while (!pq.empty()) {
    Key k = pq.top(); // top and pop and save to prev
    cout << "Top: " << k.ch << endl;
    pq.pop();
    str = str + k.ch;

    if (prev.freq > 0) pq.push(prev);

    (k.freq)--;
    prev = k;
  }
  if (n != str.length()) cout << "Not valid string " << endl;
  else cout << str << endl; // if less than length, wow
}

int main() {
  string str = "bbbaa";
  rearrangeString(str);
  return 0; 
}

