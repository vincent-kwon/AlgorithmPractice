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

/*
 * 
 * 유니코드는 0x5D0 이라고 되어있으면 D0 이 실제 몇 바이트인지를 나타내는 것이다.
 * UTF-8 로 변환되면 바이트 순서가 바뀐다. 일단 어떤 포멧인지를 보고 
 * 만약 2 바이트면 주어진 유니 코드에서 앞에 3 뒤에 2을 제외한 16 - 5 는 11바이트를
 * 슬롯 0 에서 부터 읽으면 되고 그 읽은 값을 패턴에 맞게 써주면 된다. 
 *
 * 만약 3 바이트라면 4, 6, 6 즉 16 비트를 앞에서 부터 가져와서 끊어서
 *
 * 1110 ㅌㅌㅌㅌ    10 ㅌㅌㅌㅌㅌㅌ    10ㅌㅌㅌㅌㅌㅌ
 *
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

// int u = 0x5D0; // 12 bits 0101 1101 0000 (2bytes)
// int ucode = 0xC704; (3bytes_
// int ucode = 0x057E;
int ucode = 0xE0002;

int unicode(int u) {
  int r = 0; 
  if (u >= 0 && u <= 0x7F) {
    r = u;     
  } 
  else if (u >= 0x80 && u <= 0x7FF) {
    int b2 = 0xC0;
    b2 = b2 | (u >> 6); //first 5
    int b1 = 0x80 | (u & ((1<<6)-1)); // last 6  <<======================== this is issue
    r = b2 << 8 | b1; 
  }
  else if (u >= 0x800 && u <= 0xFFFF) {
    int tmp = (u & ((1<<6)-1));
    int b1 = 0x80;
    b1 = b1 | tmp;
    u = u >> 6;
    int b2 = 0x80;
    tmp = (u & ((1<<6)-1));
    u = u >> 6;
    b2 = b2 | tmp;
    int b3 = 0xE0;
    b3 = b3 | u;
    r =  b3 << 16 | b2 << 8 | b1;
  } 
  else {
    int tmp = (u & ((1<<6)-1));
    int b1 = 0x80;
    b1 = b1 | tmp;
    u = u >> 6;
    int b2 = 0x80;
    tmp = (u & ((1<<6)-1));
    u = u >> 6;
    b2 = b2 | tmp;

    int b3 = 0x80;
    tmp = (u & ((1<<6)-1));
    u = u >> 6;
    b3 = b3 | tmp;

    int b4 = 0xF0;
    b4 = b4 | u;

    r = b4 << 24 | b3 << 16 | b2 << 8 | b1; 
  }
  return r;
}

int main() {
  int r = unicode(ucode);
  printf("unicode2: %0X\n", r);
  return 0;
}
