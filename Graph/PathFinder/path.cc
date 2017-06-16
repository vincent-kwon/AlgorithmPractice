/*
 * =====================================================================================
 *
 *       Filename:  path.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 10월 26일 07시 36분 12초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 *
 *     0 1 2 3
----------------------     
 *   0   1 2
 *   1 1   4 1
 *   2 2 4   1 
 *   3   1 1
 *
 *   what is shortest path?
 * =====================================================================================
 */

#include <iostream>
using namespace std;

#define MAP_SIZE 4
int m[MAP_SIZE][MAP_SIZE] = {
  {0,1,2,0},
  {1,0,4,1},
  {2,4,0,1},
  {0,1,1,0},
};

char visited[MAP_SIZE] = {0, };
enum visit_status {
  NO_VISIT,
  VISIT
};

int dfs(int visit_node, int accum) {
  if (visit_node == MAP_SIZE-1) {
    return accum;
  }  

  visited[visit_node] = VISIT;
  int min_value = 987654321;
  for (int target = 0; target < MAP_SIZE; target++) {
    if (m[visit_node][target] != 0 &&
        visited[target] == NO_VISIT) {
      min_value = min(min_value, dfs(target, accum + m[visit_node][target]));
    }
  }
  visited[visit_node] = NO_VISIT;
  return min_value;
}

int main() {
  int dfs_min = dfs(0, 0);
  cout << dfs_min << endl;
  //bfs();
  //dikstra();
  //aplus();
  return 0;
}
