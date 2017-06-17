#include <iostream>

using namespace std;

char str[20];

int add[20];
int sub[20];

int bet[20];

int gMin = 987654321;

int  minPalindrome(int start, int end, int sum) {
  if (start >= end) return sum;
  
  //start fix
  //// adding
  if (str[start] == str[end]) 
    gMin = min(gMin, minPalindrome(start+1, end-1, sum));

  gMin = min(gMin, minPalindrome(start+1, end, sum + bet[str[start]-'a']));

  gMin = min(gMin, minPalindrome(start, end-1, sum + bet[str[end]-'a'])); 
  
  return gMin;
}

int main() { 

  int len, num;
  cin >> len;
  cin >> num;
  cin >> str;
 
  for (int i = 0 ; i < num; i++) {
    cin >> add[i];
    cin >> sub[i];

    if (add[i] < sub[i]) bet[i] = add[i];
    else bet[i] = sub[i];
  }

  minPalindrome(0, len-1, 0);

  cout << "r:" << gMin << endl;
  return 0;
}
