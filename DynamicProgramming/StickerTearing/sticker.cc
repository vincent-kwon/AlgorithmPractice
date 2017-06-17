#include <iostream>
using namespace std;

int Map[5][2] = {
  {50, 30},
  {10, 50},
  {100, 70}, 
  {20, 10},
  {40, 60}, 
};
int Dp[5][3];

enum {
  UP,
  DOWN,
  NOT
};

int getMaxSticker(int index, int prevState) {
  if (index == 5) return 0;
  int& ret = Dp[index][prevState];

  cout << index << "," << prevState << "'s dp : " << ret << "," << Map[index][0] << ", " << Map[index][1] << endl; 

  if (ret != -1) return ret;

  if (prevState == UP) {
    ret = max(Map[index][1] + getMaxSticker(index+1, DOWN), getMaxSticker(index+1, NOT));  
  }
  else if (prevState == DOWN) {
    ret = max(Map[index][0] + getMaxSticker(index+1, UP), getMaxSticker(index+1, NOT));  
  } 
  else {
    ret = max(Map[index][1] + getMaxSticker(index+1, DOWN), Map[index][0] + getMaxSticker(index+1,UP));
    ret = max(ret, getMaxSticker(index+1, NOT));
  }
  return ret;
}
int main() {
  for (int i = 0 ; i < 5; i++)
    for (int j = 0; j < 3; j++) 
      Dp[i][j] = -1;

  int ret = getMaxSticker(0, NOT);  
  cout << "r: " << ret << endl;
  return 0;
}
