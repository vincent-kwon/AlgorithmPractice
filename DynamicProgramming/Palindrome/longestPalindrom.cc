#include <iostream>

using namespace std;

char str[20] = "abaxabaxabb";

/*

 Type 
 1. fully contained X
 2. hit end right X <= finish
 3. expands right edge also left mirror expand to left edge O <= new center
 4. epands over current edge at left edge (write only valid one) X 
 
 When to select? Under current palindrom there are several candidates like after [3] x , aba
 How to do? copy left of x to set a minimum 
 Start after min value
 if only 1,2,4 then right next of current

 Runtime complexity O(n)

 */
int getLongestPalindrome(const char* s) {
  return 0;
}

int main() {
  
  int r = getLongestPalindrome(str);

  return 0;
}
