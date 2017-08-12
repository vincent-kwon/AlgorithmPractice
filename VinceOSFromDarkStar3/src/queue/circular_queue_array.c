/*
 * =====================================================================================
 *
 *       Filename:  circular_queue_array.c
 *
 *    Description:  Basic circular queue implemented using array
 *
 *        Version:  1.0
 *        Created:  01/20/2014 06:06:40 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <stdbool.h>
#include "queue.h"

#define BEFORE_ELEMENT_IN_QUEUE -1 
#define MAX_QUEUE_CAPACITY 7
/*-----------------------------------------------------------------------------
 *  Variables
 *
 *  head: place to get data
 *  tail: place the last data already saved in 
 *
 *  case 1) when nothing in queue: head = 0, tail = -1, total_in_queue = 0;
 *          when dequeue: head is now 0 but this value is garbage.
 *                        head >= 
 *          when enqueue: tail++, tail = 0, head = 0
 *  case 2) 
 *
 *-----------------------------------------------------------------------------*/
static int head;
static int tail;
static int total_in_queue;
static int queue_array[MAX_QUEUE_CAPACITY] = {0, };

int get_total_enqueued()
{
	return total_in_queue;
}

void init_circular_array_queue() 
{
	head = 0;
	tail = BEFORE_ELEMENT_IN_QUEUE;
	total_in_queue = 0;
}

bool enqueue_to_circular_array(int insert_value)
{
	if (total_in_queue == MAX_QUEUE_CAPACITY) 
		return false;
	
	total_in_queue++;
	tail++;
	tail = tail % MAX_QUEUE_CAPACITY;
	queue_array[tail] = insert_value;
	return true;
}

bool dequeue_from_circular_array(int* output_value)
{
	if (total_in_queue == 0)
		return false;
	
	*output_value = queue_array[head];

	total_in_queue--;
	head++;
	head = head % MAX_QUEUE_CAPACITY;
	return true;
}

