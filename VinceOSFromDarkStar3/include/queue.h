/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/20/2014 06:40:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

int get_total_enqueued();

void init_circular_array_queue();

bool enqueue_to_circular_array(int insert_value);

bool dequeue_from_circular_array(int* output_value);

#endif
