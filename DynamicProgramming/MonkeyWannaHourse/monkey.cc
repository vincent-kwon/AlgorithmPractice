#include <stdio.h>
#include <iostream>
#define VC_MAX 987654321
#define MAX_ROW 200
#define MAX_COL MAX_ROW
#define MAX_K 31
enum {
  ROW_E = 0,
  COL_E,
  K_E,
};
using namespace std;

int endR, endC, totalK;
int Map[MAX_ROW][MAX_COL];
int Visit[MAX_ROW][MAX_COL];
int Dp[MAX_ROW][MAX_COL][MAX_K+1];
int Queue[200*200*31][3];
int queueHead;
int queueTail;

int move[12][2] = {
  {-2, 1},
  {-1, 2},
  { 1, 2},
  { 2, 1},
  { 2, -1},
  { 1, -2},
  {-1, -2},
  {-2, -1},
  {-1, 0},
  { 0, 1},
  { 1, 0},
  { 0, -1}
};

void enQueue(int r, int c, int k, int turn) {
  if (Map[r][c] == 1) return; 
  if (r < 0 || c < 0 || r >= endR || c >= endC) return;
  Queue[queueTail][ROW_E] = r;
  Queue[queueTail][COL_E] = c;
  Queue[queueTail][K_E] = k;
  Dp[r][c][k] = turn;
  queueTail++;
}

int deQueue() {
  return queueHead++;
}

bool isEmpty() {
  return (queueHead == queueTail);
}

int monkeyHorse(int row, int col, int k, int turn) {
  int i = 0;
  int ret = VC_MAX;
  if (k == MAX_K) {
    i = 8;
  }
  
  Visit[row][col] = 1;

  for (; i < 12; i++) {
    int nextRow, nextCol;

    nextRow = row + move[i][0];
    nextCol = col + move[i][1];

    if (nextRow == (endR-1) &&
        nextCol == (endC-1)) {
      return turn + 1;
    }
    
    // end condition
    if ( (nextRow >= 0 && nextRow < endR) &&
         (nextCol >= 0 && nextCol < endC)) {
      if (i < 8 && Map[nextRow][nextCol] != 1 && Visit[nextRow][nextCol] == 0) {
        // can move
        ret = min(ret, monkeyHorse(nextRow, nextCol, k+1, turn + 1));
        Visit[nextRow][nextCol] = 0;
      }
      else if (i >= 8 && Map[nextRow][nextCol] != 1 && Visit[nextRow][nextCol] == 0) {
        ret = min(ret, monkeyHorse(nextRow, nextCol, k, turn + 1));
        Visit[nextRow][nextCol] = 0;
      }
    }
  }
  return ret;
}
int solve() 
{
  do {
    int q = deQueue();
    cout << "dequeue: " << q << endl;
    int i = 0;
    if (Queue[q][K_E] >= MAX_K) i = 8;
    for (; i < 12; i++) {
      int r = Queue[q][ROW_E] + move[i][0];
      int c = Queue[q][COL_E] + move[i][1];
      int k = Queue[q][K_E] + (i < MAX_K)?1:0;
      if (r == endR-1 &&
          c == endC-1) return Dp[Queue[q][ROW_E]][Queue[q][COL_E]][Queue[q][K_E]] + 1;
      if (Dp[r][c][k] == -1) {
        enQueue(r,c,k,Dp[Queue[q][ROW_E]][Queue[q][COL_E]][Queue[q][K_E]] + 1);
      }
    }
  } while (!isEmpty());
}
int main() {
  freopen("input.txt","r", stdin);
  cin >> endR;
  cin >> endC;

  for (int i = 0; i < 200; i++)
    for (int j = 0; j < 200; j++) 
      for (int k = 0; k < MAX_K; k++) 
         Dp[i][j][k] = -1;
  
  for (int i = 0; i < endR; i++)
    for (int j = 0; j < endC; j++) 
      cin >> Map[i][j];
  
  //int ret = monkeyHorse(0,0,0,0);
  enQueue(0,0,0,0);
  int ret = solve();
  cout << "r:" << ret << endl;
  return 0;
}
