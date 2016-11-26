#include <iostream>
#include <stdio.h>

using namespace std;

int H,W;
int pan[25 * 10];
int dp[25 * 10][1 << 10];
 
int solve(int index) {
  if (index >= ... ) return 0;
  int next = (index % W >= W-2) ? 2: 1;
  do {
    if (pan[index+1] >= 1) status += (1<<i);
  } while (i < W)
}

int main() {
  int test_case;
  int i,j,k;
  int T;
  int result;
  freopen("input.txt", "r", stdin);
  setbuf(stdout, NULL);
  scanf("%d", &T);
  for (test_case = 1; test_case <= T; ++test_case) {
    // solve()/
  }
  return 0; 
}
