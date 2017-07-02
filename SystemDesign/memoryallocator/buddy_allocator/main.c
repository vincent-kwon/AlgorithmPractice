/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 03일 06시 01분 23초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include "buddy.h"

int main(void) {
  input_size();

  int i = 0;
  struct page *page;
  struct page *page1;

  init_memory();

  page = alloc_pages(0,2);
  page1 = alloc_pages(0,1);
 
  _free_pages(page->addr);
  _free_pages(page1->addr);
  
  for ( i = 0; i <= 9; i++) _show_free_order_list(i);

  printf("\n");
  free_memory();
  
  return 0;
}
