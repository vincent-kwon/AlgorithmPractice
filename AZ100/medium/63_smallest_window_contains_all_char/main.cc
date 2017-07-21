/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 20일 22시 08분 24초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>

using namespace std;

string s = "geeksforgeeks";
string pattern = "ork";
//string s = "this is a test string";
//string pattern = "tist";
const int MAX_CHAR = 26;
int hashArray[MAX_CHAR] = {0, };

// expected: "t stri"
// quesiton: "geeksforgeeks"
// pattern: "ork"
// answer: "ksfor"

int main() {
  int i;
  for (i=0; i < pattern.size(); i++) {
    char c = pattern[i];
    int v = c - 'a';
    hashArray[v]++;
  }
  map<char, int> answerMap;
  int matchLen = 0;
  for (i=0; i < MAX_CHAR; i++) {
    if (hashArray[i] != 0) {
      char c = 'a' + i;
      answerMap[c] = hashArray[i];
      cout << c << ":" << answerMap[c] << endl;
    }    
  }

  cout << "matchLen: " << matchLen << endl;
  int min = 987654321;
  string minStr = "";

  for (i=0; i < s.size(); i++) {
    map<char, int> checkMap = answerMap; 
    int j = i;
    for (j; j < s.size(); j++) {
      if (checkMap.count(s[j]) > 0) {
        checkMap[s[j]]--; // decrease 
        if (checkMap[s[j]] == 0) {
          // remove this key from check map
          checkMap.erase(checkMap.find(s[j]));
          // if checkMap is empty record this and break j loop;
          if (checkMap.empty()) {
            int thisLen = j - i + 1;
            if (thisLen < min) {
              min = thisLen;
              minStr = s.substr(i, thisLen);
            }
            break;
          }
        }         
      }
      else {
        continue;
      }
    } 
  }
  cout << "min: " << min << "," << minStr << endl; 
  // get required min string "tsri" for example and its sum 123, say K 
  // from location 0 to n-1
  //   prepare char hashArray [int][int][int][int]
  //   read at least K characters (index now location+K)  and if all hit stop and save gMin and gMinStr and continue;
  //   since location is moving forward, subtract count of the char of location.
  //   if hit conitnue, if not hit move index++
  return 0;
}
