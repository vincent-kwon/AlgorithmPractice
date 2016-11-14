#include <iostream>

using namespace std;

#define VC_MIN -987654321

int getLongestPalindrome() {
  string s = "abaxabaxabybaxabyb";
  int status[18] = {0, };
  int cur = 0;
  int ret = VC_MIN;
  
  while (cur < s.size()) {
    int leftEdge = cur - 1 ;
    int rightEdge = cur + 1;
    int curLeftEdge = cur;
    int curRightEdge = cur;
    int p_size = 1;

    while (leftEdge >= 0 && rightEdge < s.size()) {
      if (s.at(leftEdge) == s.at(rightEdge)) {
        p_size += 2; 
        curLeftEdge = leftEdge;
        curRightEdge = rightEdge;
        leftEdge--;
        rightEdge++;
      }
      else break;
    }

    status[cur] = p_size;
    ret = max(ret, p_size);

    if (p_size > 1) { // at least one palin
      int maxIndex = -1;
      int maxValue = VC_MIN;
      for (int offset = 1; offset + cur < curRightEdge; offset++) {
        int k = offset + cur;
        int kMirror = cur - offset;
        status[k] = status[kMirror];

        int kRightEdge = k + status[k] / 2;
        int kMirrorLeftEdge = kMirror - status[kMirror] / 2;

        if (kRightEdge < curRightEdge) continue;
        if (kRightEdge > s.size()) continue;
        if (kMirrorLeftEdge < curLeftEdge) {
          status[k] = kMirror - curLeftEdge;
          continue;
        }
        if (status[k] > maxValue) {
          maxIndex = k;
          maxValue = status[k];
        }
      }

      if (maxIndex == -1) cur++;
      else cur = maxIndex;
    } 
    else {
      cur++;
    }
  }

  return ret;
}

int main() {
  int ret = getLongestPalindrome();
  cout << ret << endl;
  return 0;
}
