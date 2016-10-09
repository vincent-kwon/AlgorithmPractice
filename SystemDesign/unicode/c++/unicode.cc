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
#include <unistd.h>
#include <assert.h>

using namespace std;

#define CHAR_1 0x01020304
#define CHAR_2 0x010203C0
#define CHAR_3 0x010203E0
#define CHAR_4 0x010203F0
//#define UNICODE_VALUE 0x5D0
//#define UNICODE_VALUE 0x3C0 // PI
//#define UNICODE_VALUE 0x3C6
#define UNICODE_VALUE 0xB2ED // 닭

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
 *
 * 0x5D0 => D0 가 첫번째 바이트인거임
 *
 * 결과를 만들 때 첫 번째 바이트에 5 | 6 | 6 이렇게 쓰기 때문에 첫 번째 바이트에 것을 먼저 써야 함
 *
 * 두 바이트 군에 속하면 원래 원본에서 11개 비트가 가능한 것이므로 
 * 
 * 110 + 5bit, 10 + 6bit
 *
 * 세 바이트 군에 속하면,
 *
 * 1110 + 4bit, 10 + 6bit, 10 + 6bit = 16 비트
 *
 * 네 바이트군 이면
 *
 * 11110 + 3bit, 10 + 6bit, 10 + 6bit, 10 + 6bit = 21비트 
 */

int main() {
  unsigned int i = UNICODE_VALUE;
  unsigned int byteMask = (1<<8)-1;
  unsigned int threeBitMask = (1<<3)-1;
  unsigned int fourBitMask = (1<<4)-1;
  unsigned int fiveBitMask = (1<<5)-1;
  unsigned int sixBitMask = (1<<6)-1;
  unsigned int first =  ((byteMask << 0) & i); // char or int?
  unsigned int second = (((sixBitMask << 8) & i)>>8);
  unsigned int third = (((sixBitMask << 16) & i)>>16);
  unsigned int fourth = (((sixBitMask << 24) & i)>>24);

  unsigned int hasNext = first & (1<<7); 
  unsigned int result; 

  if (hasNext == 0) {
    cout << "one byte unicode" << endl; 
    result = first;
  }
  else if ((hasNext = (first >> 5)) == 0x6) {
    cout << "two byte unicode " << endl;

    i = i & ((1 << 11) - 1);
    printf ("11 bit %0X\n", i);

    unsigned int firstFive = i >> 6;
    unsigned int secondSix = i & sixBitMask;

    first = first & fiveBitMask; // only first 5 110
    unsigned int r2 = (0x6 << 5) | firstFive;
    unsigned int r1 = (0x2 << 6) | secondSix;
    result = (r2 << 8) | r1;
  }
  else if ((hasNext = (first >> 4)) == 0xE) { // 1110
    cout << "three byte unicode " << endl;

    i = i & ((1 << 16) - 1);
    printf ("16 bit %0X\n", i);

    unsigned int firstFour = i >> 12; // 15 - 12
    unsigned int secondSix = (i >> 6) & sixBitMask; // 11 - 6
    unsigned int thirdSix = i & sixBitMask; // 5- 0
    
    unsigned int r3 = (0xE << 4) | firstFour;
    unsigned int r2 = (0x2 << 6) | secondSix;
    unsigned int r1 = (0x2 << 6) | thirdSix;
    result = (r3 << 16) | (r2 << 8) | r1;
  }
  else if ((hasNext = (first >> 3)) == 0x1E) { // 11110
    cout << "four byte unicode " << endl;

    i = i & ((1 << 21) -1);
    printf ("21 bit %0X\n", i);

    unsigned int firstThree = i >> 18; // 20 - 18
    unsigned int secondSix = (i >> 12) & sixBitMask;// 17 - 12
    unsigned int thirdSix = (i >> 6) & sixBitMask; // 11 - 6
    unsigned int fourthSix = i & sixBitMask;
    
    unsigned int r4 = (0x1E << 3) | firstThree;
    unsigned int r3 = (0x2 << 6) | secondSix;
    unsigned int r2 = (0x2 << 6) | thirdSix;
    unsigned int r1 = (0x2 << 6) | fourthSix;
    result = (r4 << 24) | (r3 << 16) | (r2 << 8) | r1;
  }
  else {
    assert("Bad algorithm");
  }
  //cout << "result: " << result << endl;
  printf ("Unicode (%0X)-> UTF8 : (%0X) \n", UNICODE_VALUE, result);
  return 0;
}
