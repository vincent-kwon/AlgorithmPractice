/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 19일 00시 28분 19초
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

int findoptimal(int N) {
  if (N <= 6) return N;

  int screen[N];

  int b; 
  int n;

  for (n = 1; n <= 6; n++)
    screen[n-1] = n;

  for (n = 7; n <= N; n++) {
    screen[n-1] = 0;
    for (b=n-3; b>=1; b--) {
      int curr = (n-b-1)*screen[b-1];
      if (curr > screen[n-1])
        screen[n-1] = curr;
    }
  }
  return screen[N-1];
}

int main() {
  int N;
  for (N=1; N<=20; N++) {
    cout << "Max: " << N << " = " << findoptimal(N) << endl;
  }

  return 0;
}
