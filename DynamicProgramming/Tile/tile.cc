#include <iostream>

using namespace std;

#define MAX_MAP_W 10
#define MAX_MAP_H 25
#define MAX_W MAX_MAP_W-2
#define MAX_H MAX_MAP_H-2
#define INVALID -987654321

int m[MAX_MAP_H][MAX_MAP_W] = {
 { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},

 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

bool isAvailable(int row, int col) {
  int ret;

  if (row > MAX_H || col > MAX_W) {
    return false;
  }
  
  if (m[row][col] == 0 &&
      m[row+1][col] == 0 &&
      m[row][col+1] == 0 &&
      m[row+1][col+1] == 0) 
    return true;
  else 
    return false;
}

void setOccupied(int row, int col) {
  m[row][col] = 1;
  m[row+1][col] = 1;
  m[row][col+1] = 1;
  m[row+1][col+1] = 1;
}

void setClear(int row, int col) {
  m[row][col] = 0;
  m[row+1][col] = 0;
  m[row][col+1] = 0;
  m[row+1][col+1] = 0;
}

int getMaxTile(int row, int col) {
  int ret = INVALID;

  if (row > MAX_H) return 0;

  if (col > MAX_W) {
    ret = max(ret, getMaxTile(row+1,0));
  } 
  else {
    if (isAvailable(row,col)) {
      setOccupied(row,col);
      ret = max(ret, 1 + getMaxTile(row,col+2));     
      setClear(row,col);
    }
    else {
      ret = max(ret, getMaxTile(row, col+1));
    }
  }
  return ret;
}

int main() {
  int ret = getMaxTile(0,0);
  cout << "ret = " << ret << endl;
  return 0;
}
