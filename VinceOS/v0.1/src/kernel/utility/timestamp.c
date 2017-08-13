/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* template.c  Convenience source including all other headers
 *
 *  Copyright 2012 VINCETECH Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 * 
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "timestamp.h"


static void
_timestamp_stringshared_free_cb(void *data)
{
   free(data);
}
void init_timestamp() 
{
}


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
struct timeval*
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
	return tv;
}

struct timeval*
end_timestamp(const char *start_mark, bool print_result_now)
{
	struct timeval* tv = NULL;
        tv = (struct timeval *)malloc(sizeof(struct timeval));
        if (!tv)
        {
                fprintf(stderr, "Failed to allocate timeval\n");
                return NULL;
        }
	gettimeofday(tv,NULL); //saved in tv.tv_sec, tv.tv_usec (microseconds)
	timestamp_record *retrieved_entry = NULL;
	if(!retrieved_entry) 
	{
		fprintf(stderr, "Failed to retrieve start timestamp_record.");
		return NULL;
	}
	retrieved_entry->end_time = tv;

	if (print_result_now == true) 
	{
		//calculate duration
		retrieved_entry->duration = timeval_diff(retrieved_entry->end_time, retrieved_entry->start_time);
		fprintf(stdout,"TIMEDIFF[%s] = %lld(ms)\n", start_mark, retrieved_entry->duration);
	}
	return tv;

}

