/*
 * =====================================================================================
 *
 *       Filename:  travel.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 09일 22시 41분 05초
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

#define NUM 5 
#define VC_MAX 987654321
#if 0
int m[NUM][NUM] = {
  { 0, 34, 36, 37, 31, 33, 35 },
  { 34, 0, 29, 23, 22, 25, 24 },
  { 36, 29, 0, 17, 12, 18, 17 },
  { 37, 23, 17, 0, 32, 30, 29 },
  { 31, 22, 12, 32, 0, 26, 24 },
  { 33, 25, 18, 30, 26, 0, 19 },
  { 35, 24, 17, 29, 24, 19, 0 },
};
#endif

int m[NUM][NUM] = {
 {0, 2, 0, 6, 1},
 {1, 0, 4, 4, 2},
 {5, 3, 0, 1, 5},
 {4, 7, 2, 0, 1},
 {2, 6, 3, 6, 0},
};

//int dp2[NUM][NUM] = {0, };
int dp4[NUM][NUM][NUM][NUM];

int getSpan(const int start, const int num, const int value, const int end) {
  int& ret = dp4[start][num][value][end];

  if (ret != -1) return ret;  

  if (num <= 0) return ret = m[start][end];
 
  ret = VC_MAX;
 
  for (int i = 0; i < NUM; i++) {
    int newValue = value;
    int mask = (1 << i);
    if ((value & mask) != 0) {
      newValue = newValue & (~mask); // erase
      ret = min(ret, getSpan(start, num-1, newValue, i)+m[i][end]);
    }
  }
  return ret;
}

int main() {
  for (int i1 = 0; i1 < NUM; i1++)
    for (int i2 = 0; i2 < NUM; i2++)
      for (int i3 = 0; i3 < NUM; i3++)
        for (int i4 = 0; i4 < NUM; i4++)
          dp4[i1][i2][i3][i4] = -1;

  int ret = getSpan(0, 4, 1<<1|1<<2|1<<3|1<<4, 0);
  cout << "ret: " << ret << endl;
  return 0;
}
