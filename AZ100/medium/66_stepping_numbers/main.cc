/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 07시 29분 25초
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

// U & V if V can be transformed into U in this manner
//
//  U*10 + lastDigit+1
//  12 => 121
//  12 => 123

void bfs(int n, int m, int num) {
  queue<int> q;
  q.push(num);

  while (!q.empty()) {
    int stepNum = q.front();
    q.pop();
    if (stepNum <= m && stepNum >= n) {
      cout << stepNum << " " << endl;
    }

    if (num == 0 || stepNum > m) continue;
 
    int lastDigit = stepNum % 10;
    int stepNumA = stepNum * 10 + lastDigit - 1;
    int stepNumB = stepNum * 10 + lastDigit + 1;
  
    if (lastDigit == 0) q.push(stepNumB);

    else if (lastDigit == 9) q.push(stepNumA);

    else {
      q.push(stepNumA);
      q.push(stepNumB);
    }
  }
}

void displaySteppingNumbers(int n, int m) {
  for (int i = 0 ; i <= 9; i++) 
    bfs(n,m,i);
}

int main() {
  displaySteppingNumbers(0,1000); 
  return 0;
}
