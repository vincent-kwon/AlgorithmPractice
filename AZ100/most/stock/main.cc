/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 23일 08시 36분 15초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stack>

using namespace std;

void calculateSpan(int price[], int n, int S[]) {
  stack<int> st;
  st.push(0);
  S[0] = 1;

  for (int i = 1; i < n; i++) {
    while (!st.empty() && price[st.top()] <= price[i]) {
      cout << i << " " << "st.top() " << st.top() << " is popping out " << endl;
      st.pop();
    }
    if (st.empty()) {
      S[i] = i+1;
      cout << i << " since st is empty, add i+1 to s[i] " << S[i] << endl;
    }
    else {
      S[i] = (i-st.top());
      cout << i << " since st is not empty, i-st.top()( " << st.top() << " which is " << S[i] << endl;
    }
    cout <<i << " S[" << i << "] " << S[i] << ", empty: " << st.empty() << ", count: " << st.size() << ", st.top: " << (st.empty()?0:st.top()) << endl;
    st.push(i);
  }
}

void printArray(int arr[], int n) {
  for (int i = 0 ; i < n; i++) cout << arr[i] << " ";
  cout << "" << endl;
}

int main() {
  int price[] = { 10, 4, 5, 90, 120, 80 };
  int n = sizeof(price)/sizeof(price[0]);

  int S[n];
  printArray(price, n);
  calculateSpan(price,n,S);

  printArray(S,n);
  return 0;
}

