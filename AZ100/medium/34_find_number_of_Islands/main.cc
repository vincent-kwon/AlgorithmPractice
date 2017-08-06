/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 06시 18분 27초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

// memo: main idea is do to DFS
//
// 1. for all nodes in matrix, visit them with DFS unless already visited (traversal issue)
// 2. just count DFS 
//  
//    when navigating, 
//
//    static int rowNbr[] = {-1,-1,-1,0,0,1,1,1}; // memo: this pattern
//    static int colNbr[] = {-1,0,1,-1,1,-1,0,1};
//
//    for (int k = 0; k < 8; k++)
//
//    visit => row+rowNbr[k], col+colNbr[k] 
//
//
