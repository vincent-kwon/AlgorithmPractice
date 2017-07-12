/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 13일 04시 51분 50초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> v = {10, 2, 3, 4, 5, 9, 7, 8};

int INF = 987654321;
#define  NUM  8
#define  VAL  23

int A[NUM+1][VAL+1] = {0, };

int main() {
  for (int i = 0; i <= NUM; i++)
    for (int k = 0; k <= VAL; k++) {
      if (k != 0) A[i][k] = INF;
      else A[i][k] = 0;
    }

  A[0][0] = 0;

  sort(v.begin(), v.end());
  //cout << v[0] << endl;
  for (int i = 1; i <= NUM; i++) {
    for (int k = 1; k <= VAL; k++) {
      if (k < v[i-1]) {
        A[i][k] = A[i-1][k];
        //cout << "assign " << i << "," << k << " = " << A[i][k] << endl;
      }
      else {
        if (A[i-1][k] != INF) {
          A[i][k] = A[i-1][k]; 
          //cout << "Inherit " << i << "," << k << " = " << A[i][k] << endl;
        }
        else if (A[i-1][k - v[i-1]] != INF) {
          A[i][k] = i;
          //cout << "New " << i << "," << k << " = " << A[i][k] << endl;
        }
      }
    }
    int count = 0; 
    vector<int> result;
    int tmp = i; 
    int remaining = VAL;
    if (A[tmp][VAL] != INF) {
      cout << "check match: " << endl;
 
      tmp = A[tmp][remaining];
      while (tmp > 0) {
        cout << "index: " << tmp << ", value: " << v[tmp-1] << ", current R: " << remaining << endl;
        remaining = remaining - v[tmp-1];
        //cout << "next R: " << remaining << endl;
        tmp = A[tmp][remaining];
      }
      cout << "end match" << endl;
    } 
  }
  return 0;
}
