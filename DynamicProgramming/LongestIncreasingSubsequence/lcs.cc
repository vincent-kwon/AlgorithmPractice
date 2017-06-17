#include <iostream>

using namespace std;

// 6: -1, 2, 3, 7, 9, 11
int arr[11] =  {  3, 4, -1, 5, 8, 2, 3, 12,  7,  9, 11 };
int from[11] = { -1,-1,-1 ,-1,-1,-1,-1, -1, -1, -1, -1 }; 
int minIndex[11] =  { 0, };
int maxLen = 0;
/*

  R 
  0 -1 <== from which (prev value)
  1 -1
  3 -1

    (zero one element array)
  T 0 1 2 3 4 5 6 7 8 9 10 <== 2 ISS length 1 (3, 4), 1 ISS length 2 (34)

  Store index of minimum value of the last value of the subsequence 

  Binary search [6] 3 since it is bigger than 0 and less than biggest

  Len: 0 <== current len 
 */

int getLCS() {
  int len = 0;
  minIndex[len] = 0;
  for (int i = 1; i < 11; i++) {
    if (arr[minIndex[len]] < arr[i]) {
      from[i] = minIndex[len];
      len++;
      minIndex[len] = i;
      continue;      
    }
    int cur = arr[i];
    for (int j = 0; j <= len; j++) {
      if (j == 0 && cur < arr[minIndex[0]]) { 
        minIndex[j] = i;
        from[i] = -1;
        break;
      }
      else if (j > 0 && cur < arr[minIndex[j]] 
               && cur > arr[minIndex[j-1]])  {
        minIndex[j] = i;
        from[i] = minIndex[j-1];
        break;
      }
    }
  }

  int tmp = minIndex[len];
  while (from[tmp] != -1) {
    cout << arr[tmp] << endl;
    tmp = from[tmp];
  }   
  cout << arr[tmp] << endl;

  return len+1;
}

int main() {
  int ret = getLCS();
  cout << "r: " << ret << endl;
  return 0;
}
