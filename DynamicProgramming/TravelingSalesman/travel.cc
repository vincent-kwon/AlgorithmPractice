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

#define NUM 4
#define VC_MAX 987654321

int m[NUM][NUM] = {
  { 0, 1, 15, 6 },
  { 2, 0, 7, 3 },
  { 9, 6, 0, 12 },
  { 10, 4, 8, 0 },
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

  int ret = getSpan(0, 3, 1<<1|1<<2|1<<3, 0);
  cout << "ret: " << ret << endl;
  return 0;
}
