/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 06시 50분 38초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * memo: Kadane's algorithm: for negative set max_ending_here to 0
 *
 * for (int i = 0 ; i < size; i++) {
 *   max_ending_here = max_ending_here + a[i];
 *   if (max_so_far < max_ending_here) max_so_far = max_ending_here;
 *   if (max_ending_here < 0) max_ending_here = 0;
 * }
 * =====================================================================================
 */


