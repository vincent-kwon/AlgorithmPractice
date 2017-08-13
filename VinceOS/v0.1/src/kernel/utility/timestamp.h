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

#ifndef __VC_TIMESTAMP_H__
#define __VC_TIMESTAMP_H__

#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFSIZE 1024
#define PATHSIZE 128

typedef struct _timestamp_record {
    struct timeval* start_time;
	char start_location[PATHSIZE];
	struct timeval* end_time;
	char end_location[PATHSIZE];	
	long long duration;
} timestamp_record;

/**
  * Starting the measurement by marking the point as the received string.
  * If there is an existing mark for the received string, it will be 
  * replaced by the latest one. 
  *
  */

void init_timestamp();

struct timeval*
start_timestamp(const char *start_mark);

struct timeval*
end_timestamp(const char *start_mark, bool print_now);

#endif /* __VC_TIMESTAMP_H__ */
