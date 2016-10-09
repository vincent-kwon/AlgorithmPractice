/*
 * =====================================================================================
 *
 *       Filename:  unicode.cc
 *
 *    Description:  Ascii MSB has the indication to read next byte or not
 *
 *        Version:  1.0
 *        Created:  2016년 10월 10일 00시 11분 52초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdio.h>

using namespace std;

#define CHAR_1 0x01020304
#define CHAR_2 0x010203C0
#define CHAR_3 0x010203E0
#define CHAR_4 0x010203F0
#define UNICODE_VALUE 0x5D0
/*
 * alfre unicode value 0x5D0 == U+05D0
 *
 * Two byte unicode is
 *
 * 0000 0101 1101 0000 => 11 bits
 *
 * two bits style is 110xxxxx, 10yyyyyy
 *
 * Now use valid 11 bit to xxxxx, yyyyy
 *
 * Then 110-10111 10-010000 is value
 *      1101 0111 1001 0000
 *      D    7    9    0
 */

int main() {
  unsigned int i = UNICODE_VALUE;
  unsigned int mask = (1<<8)-1;
  unsigned int mask4 = (1<<5)-1;
  unsigned int mask3 = (1<<6)-1;
  unsigned int first =  ((mask << 0) & i); // char or int?
  unsigned int second = (((mask3 << 8) & i)>>8);
  unsigned int third = (((mask3 << 16) & i)>>16);
  unsigned int forth = (((mask3 << 24) & i)>>24);

  // cout << first << "," << second << "," << third <<"," << forth << endl;
  // assume forth is the first byte to read
  unsigned char mask2 = 1<<7;
  unsigned int hasNext = first & mask2; 

  unsigned int result; 

  if (hasNext == 0) {
    cout << "one byte unicode" << endl; 
    result = first;
  }
  else if ((hasNext = (first >> 5)) == 0x6) {
    cout << "two byte unicode " << endl;
    first = first & mask4; // only first 5
    //printf ("First :(10) %d,  %0x\n", first, first);
    //printf ("Second : (10) %d, %0x\n", second, second);
    unsigned int r2 = (0x6 << 5) | first;
    unsigned int r1 = (0x2 << 6) | second;
    result = (r2 << 8) | r1;
  }
  else if ((hasNext = (first >> 4)) == 0xE) {
    cout << "three byte unicode " << endl;
    //how to combine one / two / three
  }
  else if ((hasNext = (first >> 3)) == 0x1E) {
    cout << "four byte unicode " << endl;
    //how to combine one / two /three / four
  }
  else {
    cout << "stupid" << endl;
  }
  cout << "result: " << result << endl;
  printf ("%0x\n", result);
  return 0;
}
