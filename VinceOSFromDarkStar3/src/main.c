/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* template.c  Convenience source including all other headers
 *
 *  Copyright 2013 vincentech corporation.
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

//headers
#include <unistd.h>  //optarg 
#include <stdlib.h>  //malloc, free
#include <stdio.h>   //printf
#include <string.h>  //memset
#include <stdbool.h> //true, false
#include "log4c.h"
#include "rdb.h"

extern int start_app_launcher_daemon(char *);
static log4c_category_t* logcat = NULL;

int main (int argc, char **args) {
  int opt = 0;
  int chpid = 0;
  char *server_port = NULL;
  char port_number[256];
  char *dummyArgsv[] = {""};
  int i;

#if 0
  init_circular_array_queue();

  for (i = 0 ; i < 100 ; i++) 
  {
    if (enqueue_to_circular_array(i))
    {
      printf("enqueued: %d(total: %d)\n", i, get_total_enqueued());
    }
    else 
    {
      printf("enqueue failed for %d\n", i);
    }

    if (i%2) 
    {
      int received; 
      if (dequeue_from_circular_array(&received)) 
      {
        printf("dequeued: %d(total: %d)\n", received, get_total_enqueued());
      }
      else 
      {
        printf("dequeu failed\n"); 
      }
    }
  }
  
  rdb_init(); 

  rdb_insert_node(100);
  rdb_insert_node(10);
  rdb_insert_node(1);
  rdb_insert_node(4);
  rdb_insert_node(25);
  rdb_insert_node(33);
  rdb_insert_node(8);
  rdb_insert_node(10000);
  rdb_insert_node(100000);
  //rdb_insert_node(1000000);
#endif

  if (log4c_init()) {
    printf("logger init failed....");
    return EXIT_FAILURE; 
  }
  else {
    logcat = log4c_category_get("darkstar3.main");
    if (!logcat) {
      printf("log4c_category_get failed....");
      return EXIT_FAILURE; 
    }
    else {
      log4c_category_log(logcat, LOG4C_PRIORITY_DEBUG, "powered by log4c.");
    }
  }

  if (argc != 3) {
    printf("usage: darkstar3 -p port_number\n");
    return EXIT_FAILURE; 
  }

  while ((opt = getopt(argc, args, "p:")) != -1) {
    switch (opt) {
    case 'p':
	memcpy(port_number, optarg, 16); 
	server_port = port_number;
	break;
    default:
	break;
    }
  }

  
  printf("fork\n");
  //start system controller daemeon
  chpid = fork();

  if (chpid > 0) { // for a new forked process
    printf("fork system controller.\n");
    //execv("", dummyArgsv); //system controller daemon 
  }
  else if (chpid < 0) {
    printf("fork failed.\n");
    return EXIT_FAILURE; 
  }
  else { //for the main process
    chpid = fork();
    if (chpid > 0) { // for a new forked process
     printf("fork launcher GUI application...\n"); 
     //execv("", dummyArgsv); //launcher application
    }
    else if (chpid < 0) {
      printf("fork failed.\n");
      return EXIT_FAILURE; 
    }
    else { //for the main process
      start_app_launcher_daemon(server_port);
    }
  }
  return EXIT_SUCCESS;
} //end of main
