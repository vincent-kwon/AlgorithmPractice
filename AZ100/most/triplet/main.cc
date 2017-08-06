/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 22일 23시 37분 00초
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

//int arr[] = {3, 1, 4, 6, 5};
int arr[] = {10, 4, 6, 12, 5};

int checkTriplet(int arr[], int size, int sum, int used[]) {
  int count = 0;
  for (int i = 0; i < size; i++) { 
    if (used[i] == 1) count++;
  }

  if (count > 3) return 0;
  else if (count == 3) {
    if (sum == 0) return 1; 
    else return 0;
  }
  
  if (sum <= 0) return 0;

  for (int i = 0; i < size; i++) {
    if (used[i] == 0) {
      // not used
      used[i] = 1;
      if (checkTriplet(arr, size, sum-arr[i]*arr[i], used)) return 1;
      used[i] = 0;
    }
  }
  return 0;
}

int getTriplet(int arr[]) { // memo: sizeof(arr) for arr[] is 4 bytes
  int size = 5;
  for (int i = 0; i < size; i++) {
    int used[] = {0, 0, 0, 0, 0};
    used[i] = 1;
    if (checkTriplet(arr, size, arr[i]*arr[i], used)) return 1;
    used[i] = 0;
  }
  return 0;
}

int main() {
  int ret = getTriplet(arr);
  if (ret) cout << "there is a triplet" << endl;
  else cout << "can't find a triplet" << endl;  
  return 0;
}
