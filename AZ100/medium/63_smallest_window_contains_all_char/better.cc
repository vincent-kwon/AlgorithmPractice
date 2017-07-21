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

string s = "this is a test string";
string pattern = "tist";
//string s = "geeksforgeeks";
//string pattern = "ork";

const int MAX_CHAR = 26;
int hashArray[MAX_CHAR] = {0, };
int main() {
  int i;
  for (i=0; i < pattern.size(); i++) {
    char c = pattern[i];
    int v = c - 'a';
    hashArray[v]++; // memo: hash
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

  int prevJ = -1; // we know prevJ was made 
  map<char, int> prevMap;

  for (i=0; i < s.size(); i++) {
    map<char, int> checkMap = answerMap; // memo: copy map
    int j = i;
    if (prevJ != -1) {
      checkMap = prevMap; // memo: do not repeat same routine again and again
      j = prevJ + 1; // done by prevJ: prevj already done 
      char c = s[i-1];
      if (answerMap.find(c) != answerMap.end()) { // memo: find function and checking with end()
        if (checkMap.find(c) != checkMap.end()) checkMap[c]++;
        else checkMap[c] = 1;
      }
    }
    for (j; j < s.size(); j++) {
      // in this case len should - 1 more
      if (checkMap.empty()) { // in this case only removing works
         j = j - 1; // memo: why subtract? since now preJ + 1 but this case done without erasing. happy case. restore -1 now here
         int thisLen = j - i + 1;
         if (thisLen < min) {
            min = thisLen;
            minStr = s.substr(i, thisLen); // memo: substr index, length
         }
         break;
      }
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
    // case found: can utilize last index value
    if (checkMap.empty()) {
      prevJ = j;
      prevMap = checkMap;
    }
    else {
      prevJ = -1;
    }
    // case not found: still all value suched so can save prej much better 
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
