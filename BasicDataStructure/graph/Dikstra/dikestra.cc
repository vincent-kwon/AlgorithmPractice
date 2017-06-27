/*
 * =====================================================================================
 *
 *       Filename:  dikestra.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 27일 07시 15분 48초
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
#define INF 987654321

int array[8][8] =  {
  { INF, 8,   11,  9,   INF, INF, INF, INF },
  { INF, INF, INF, INF, INF, 10,  INF, INF },
  { INF, INF, INF, INF, 8  , INF, 8  , INF },
  { INF, 6  , 3  , INF, INF, 1,   INF, INF },
  { INF, INF, INF, INF, INF, INF, 7,   INF },
  { INF, INF, INF, INF, INF, INF, INF, 2   },
  { INF, INF, INF, INF, INF, INF, INF, 5   },
  { INF, INF, INF, INF, 4  , INF, INF, INF },
};

int sum[8] = {0, INF, INF, INF, INF, INF, INF, INF};
unsigned char visit_bit = 0;
  // put 0 as visited
  // put 0 as distance fo array[0]
  // select minimum element not visited
  // once selected, update adjacent values from the selected
  // select smallest among reachable
  // mark this selected
void dikstra() {
  visit_bit |= 1;
  
  for (int i = 0; i < 8; i++) {
    if (array[0][i] != INF) {
      sum[i] = array[0][i];
    }
  }

  while (visit_bit != ((1 << 8)-1)) {
    int nextMin;
    int nextMinValue = INF;

    for (int i = 0; i < 8; i++) {
      int nextBit = 1 << i;
      if (visit_bit & nextBit) { // if visited
        for (int j = 0; j < 8; j++) { // check agjacent
          if ((array[i][j] != INF) && ((visit_bit & (1<<j)) == 0)) { // if adjacent && not visited
            if (sum[j] < nextMinValue) { // check smallest
              nextMin = j;
              nextMinValue = sum[j];
            }
          }
        }
      }
    }
    visit_bit |= (1 << nextMin); // check visited
    for (int i = 0; i < 8; i++) {
      if (array[nextMin][i] != INF) {
        if ((array[nextMin][i] + sum[nextMin]) < sum[i]) {
          sum[i] = sum[nextMin] + array[nextMin][i]; // update ajacent of the next one
        }
      }
    }
  }
}

int main() {
  dikstra();
  for (int i = 0 ; i < 8; i++) cout << sum[i] << endl;
  return 0;
}
