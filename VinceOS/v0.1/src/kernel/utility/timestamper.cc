/*
 * =====================================================================================
 *
 *       Filename:  timestamper.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 08월 13일 01시 34분 11초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include "timestamper.h"
#include <exception>
#include <stdexcept>

using namespace std;

class NoEntryException : public runtime_error {
 public:
  NoEntryException(char const* message) : runtime_error(message) {
  }
  virtual const char* what(const string& msg) const noexcept {
    string s = "no previous entry";
    return s.c_str();
  }
};

class DuplicatedEntryException : public runtime_error {
 // memo_201706: invalid_argument, bad_alloc, bad_cast, out_of_range, overflow_error, underflow_error
 public:
  DuplicatedEntryException(char const* message) : runtime_error(message) {
  }
  virtual const char* what() const noexcept { // memo_201706
    string s = "duplicated entry";
    return s.c_str();
  }
};


static long long 
timeval_diff(struct timeval *end_time,
             struct timeval *start_time
            )
{
	struct timeval temp_diff;
	struct timeval *difference = &temp_diff;

        //end_sec is always greater than start_sec
	difference->tv_sec = end_time->tv_sec - start_time->tv_sec;
        //however, end_usec might be smaller than start_usec.
	difference->tv_usec= end_time->tv_usec - start_time->tv_usec;

	/* Using while instead of if below makes the code slightly more robust. */
        //check for example, usec_diff = 500 - 700 = -200 
        //then now add 1,000,000 to the diff: 999,800
        //if still below zero, then keep checking decreasing sec.
	while(difference->tv_usec < 0)
	{
		difference->tv_usec+=1000000;
		difference->tv_sec -=1;
	}
        //return in microseconds
	return 1000000LL*difference->tv_sec + difference->tv_usec;
} /* timeval_diff() */


/**
  * @return: returning index used to hold the record in static array. s
  */
timestamp_record*
start_timestamp(const char *start_mark) 
{
  struct timeval* tv = NULL;
  timestamp_record *new_entry = (timestamp_record *)malloc(sizeof(timestamp_record));
  if (!new_entry) 
  {
    fprintf(stderr, "Failed to initialize timestamp_record.");
    return NULL;
  }	
  sprintf((char *)new_entry->start_location, "%s,%d" , __FILE__, __LINE__);
  tv = (struct timeval *)malloc(sizeof(struct timeval));
  if (!tv)
  {
    fprintf(stderr, "Failed to allocate timeval\n");
    return NULL;
  }
  gettimeofday(tv,NULL); //saved in tv.tv_sec, tv.tv_usec (microseconds)
  new_entry->start_time = tv;
  return new_entry;
}

timestamp_record*
end_timestamp(const char *start_mark, timestamp_record* retrieved_entry)
{
  struct timeval* tv = NULL;
  tv = (struct timeval *)malloc(sizeof(struct timeval));
  if (!tv)
  {
    fprintf(stderr, "Failed to allocate timeval\n");
    return NULL;
  }
  gettimeofday(tv,NULL); //saved in tv.tv_sec, tv.tv_usec (microseconds)
  if(!retrieved_entry) 
  {
    fprintf(stderr, "Failed to retrieve start timestamp_record.");
    return NULL;
  }
  retrieved_entry->end_time = tv;
  //calculate duration
  retrieved_entry->duration = timeval_diff(retrieved_entry->end_time, retrieved_entry->start_time);
  fprintf(stdout,"TIMEDIFF[%s] = %lld(ms)\n", start_mark, retrieved_entry->duration);
  return retrieved_entry;
}

Timestamper::Timestamper() {
  cout << "const" << endl;
}

Timestamper::~Timestamper() { // memo-20170812: no need to add virtual in implemetation
  cout << "dest" << endl;
}

void Timestamper::enter(string mark) {
  cout << "enter:" << endl;
  if (timemap.count(mark) != 0) {
    throw DuplicatedEntryException("");
  }
  timemap[mark] = start_timestamp(mark.c_str());
}

void Timestamper::exit(string mark, bool printResult) {
  cout << "exit:" << endl;
  if (timemap.count(mark) == 0) {
    throw NoEntryException("");
  }
  timemap[mark] = end_timestamp(mark.c_str(), timemap[mark]);
}

void Timestamper::print(string mark) {
  cout << "print: " << endl;
}

void Timestamper::printAll() {
  cout << "printAll:" << endl;
}

