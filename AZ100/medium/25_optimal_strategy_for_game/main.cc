/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 10일 16시 57분 15초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *    2: bigger wins always
 *    3: ??                           I
 *    4: ?? no simple rule, left +  A B C D bigger always win if B is big, then D. 
 *                                                            if C is big, then A.
 *                                                            A + 
 *
 *    2: bigger wins
 *    3: 15 - 3 - 7 <==== 15 + min(3, 7) or 7 + min(15,3)    
 *    4: left + getValueoLeave(1-3) vs right + autoLeave(0-2) => bigger select                                                     
 *    5: left + 
 * =====================================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

int array[] = {20, 30, 2, 2, 2, 10};
int selected = {0, };
vector<int> gRes;
vector<int> gOpp;

int getMax(int start, int end, int& evenReturn, int& oddReturn) {
  int nums = end - start + 1;

  if (nums == 2) { // 2, 1 all
    evenReturn = max(array[start], array[end]);
    oddReturn = min(array[start],array[end]);
  } 
  else if (nums > 2) {
    int val1, val2;
    int nextEven, nextOdd;
    int nextEven2, nextOdd2; 
    if (nums % 2) {
      // odd turn
      getMax(start+1, end, nextEven, nextOdd);
      val1 = array[start] + nextOdd; 

      getMax(start, end-1, nextEven2, nextOdd2); 
      val2 = array[end] + nextOdd2;

      if (val1 > val2) {
        oddReturn = val1;
        evenReturn = nextEven;
      } 
      else {
        oddReturn = val2;
        evenReturn = nextEven2;
      }
    }
    else {
      // even turn
      getMax(start+1, end, nextEven, nextOdd);
      val1 = array[start] + nextEven; 

      getMax(start, end-1, nextEven2, nextOdd2); 
      val2 = array[end] + nextEven2;

      if (val1 > val2) {
        oddReturn = nextOdd;
        evenReturn = val1;
      } 
      else {
        oddReturn = nextOdd2;
        evenReturn = val2;
      }
    }
  }
  return 0;
}  

int main() {
  const int num = sizeof(array)/sizeof(int);
  int nextOdd, nextEven;
  int ret = getMax(0, num-1, nextEven, nextOdd);
  cout << nextEven << endl;
  return 0;
}
