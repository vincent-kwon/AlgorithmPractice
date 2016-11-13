#include <iostream>

using namespace std;

// 6: -1, 2, 3, 7, 9, 10
char arr[20] = { 3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10 };

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
int main() {

  return 0;
}
