/*
 * =====================================================================================
 *
 *       Filename:  post_delivery.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 23일 05시 43분 22초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdio.h>

#define VC_MAX 987654321
#define VC_MIN -987654321

using namespace std;

int Map[100][100];
int go[10];
int stop[10];
int N,E,T;
int dp[100][1024];

int getBitCount(int i) {
  int count = 0;
  while (i > 0) {
    count++;
    i = i & (i-1);   
  }
  return count;
}

int tsp(int startNode, int maxBit, int value) {
  int& ret = dp[startNode][value];
  if (ret != VC_MAX) return ret;
  if (value == 0) return Map[startNode][1];
  for (int i = 0; i < maxBit; i++) {
    int bitMask = 1 << i;
    if (bitMask & value) {
      int newValue = ~bitMask & value;      
      int tmp = Map[startNode][go[i]] + 
                Map[go[i]][stop[i]] +
                tsp(stop[i], maxBit, newValue);
      ret = min(ret, tmp);
    }
  }

  return ret;
}

int main() {
  int test;
  freopen("input.txt", "r", stdin); 
  cin >> test;
  while (test-- > 0) {
    cin >> N;
    cin >> E;
    cin >> T;
    for (int i = 1; i <= N; i++) {
      for (int k = 1; k <= 1024; k++) {
        dp[i][k-1] = VC_MAX;
      }
    }    
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (i != j) Map[i][j] = VC_MAX;
        else Map[i][i] = 0;
      }
    }    
    for (int i = 1; i <= E; i++) {
      int s, e, cost;
      cin >> s;
      cin >> e;
      cin >> cost;
      Map[s][e] = cost;
    }
    for (int i = 0; i < T; i++) {
      int s, e;
      cin >> s;
      cin >> e;
      go[i] = s;
      stop[i] = e;
    }
    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          if (Map[i][j] > (Map[i][k] + Map[k][j])) Map[i][j] = Map[i][k] + Map[k][j];
        }
      }
    }
    const int bits = (1 << T) - 1; 
    int tmp = T; 
    int ret = VC_MAX;
    int bitCount = getBitCount(bits);
    int border = (tmp + 1)/2;
    while (tmp >= border) {
      int decBits = bits;
      int innerBorder = (decBits+1)/2;
      while (decBits >= innerBorder) {
        if (getBitCount(decBits) == tmp) {
          int antibits = ~decBits & bits;
          int ret1 = tsp(1, bitCount, decBits); 
          int ret2 = tsp(1, bitCount, antibits);
          int tmp = max(ret1, ret2);
          ret = min(ret, tmp);
        }
        decBits--;
      }
      tmp--;
    }
    cout << "answer: " << ret << endl; 
  }
  return 0;
}
