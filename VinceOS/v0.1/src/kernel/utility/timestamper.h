/*
 * =====================================================================================
 *
 *       Filename:  timestamper.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 08월 13일 01시 17분 51초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * - start/exit time stamp
 * - shared library
 * - throw exception (custom no entry exist) if mark is not existing
 * - throw exception (custom or not) if mark is already in the map
 * =====================================================================================
 */
#pragma once

#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <map>

#define BUFFSIZE 1024
#define PATHSIZE 128

typedef struct _timestamp_record {
  struct timeval* start_time;
  char start_location[PATHSIZE];
  struct timeval* end_time;
  char end_location[PATHSIZE];	
  long long duration;
} timestamp_record;

class Timestamper {
 public:
  void enter(std::string mark); 
  void exit(std::string mark, bool printResult = false);
  void print(std::string mark);
  void printAll();
  void releaseAll();
  Timestamper();
  std::map<std::string, timestamp_record*> timemap;
  virtual ~Timestamper();
};
