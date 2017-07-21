/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 21일 07시 04분 39초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <memory.h>

using namespace std;

string str = "bb";
string pattern = "*";


bool isMatch(string str, string pattern) {
  if (pattern.size() == 0) return str.size() == 0; // memo: Money ball, input check 

  int dp[pattern.size()+1][str.size()+1];

#if 0 
  for (int i = 0; i <= pattern.size(); i++) {
    for (int j = 0; j <= str.size(); j++) {
      dp[i][j] = 0;
      cout << dp[i][j] << endl;
    }
  }
#else
  memset(dp, 0, sizeof(dp)); // memo: array init, array size of bytes are by sizeof(dp) = 24

/*for (int i = 0; i <= pattern.size(); i++) {
    for (int j = 0; j <= str.size(); j++) {
      cout<< i << "," << j << ":" << dp[i][j] << endl;;
    }
  }*/
#endif

  dp[0][0] = 1;
  
  for (int i = 1; i <= pattern.size(); i++) {
    for (int j = 1; j <= str.size(); j++) {
      int consumeOne = 0;
      int consumeMore = 0;
        // cout << i << "," << j << endl;
      if (pattern[i-1] == '*') {
        // use
        // cout <<" * " << endl; 
        consumeOne = dp[i-1][j-1];
        consumeMore = dp[i][j-1];
        // cout << "co:" << consumeOne << endl;
        // cout << "cm:" << consumeMore << endl;
        if ((consumeOne+consumeMore) > 0) dp[i][j] = 1;
      }
      else if (pattern[i-1] == '?') {
        dp[i][j] = dp[i-1][j-1];
      }
      else {
        if (pattern[i-1] == str[j-1]) {
          dp[i][j] = dp[i-1][j-1];
        } 
        else dp[i][j] = 0;
      }
    }
  }
  /*for (int i = 0; i <= pattern.size(); i++) {
    for (int j = 0; j <= str.size(); j++) {
      cout<< i << "," << j << ":" << dp[i][j] << endl;;
    }
  }*/
  if (dp[pattern.size()][str.size()] == 1) return true;
  else return false;
}

int main() {
  cout << "str:" << str << endl;
  cout << "pattern:" << pattern << endl;
  if (isMatch(str, pattern)) cout << "Match" <<endl;
  else cout << "No match" << endl;
  return 0;
}
