#include <iostream>

using namespace std;
#define MAX_GAL 1000
#define MAX_HALL (MAX_GAL-1) 
int g[MAX_GAL][MAX_GAL] = {0, };
int v[MAX_GAL] = {0, };

int dfs (int p, int N, int H)
{
  int i, j, k;
  int ret = 0;

  if (v[p] == 1) return 0;
  else v[p] = 1;    

  for (i = 0 ; i < N; i++) 
  {
    if (g[p][i] == 1) 
    {
      ret += dfs(i, N, H); // do not save return value;
    }
  } 
  return ret; 
}

int main() 
{
  // starting 6:30
  // g: gallery 0 ~ g-1 (may not one component)
  // h: connected hallways
  // Q. how many camera needed to cover all area?
  // 0 1
  // 1 2
  // 1 3
  // 2 5
  // 0 4
  // how many components in this graph?
  // 1. make graph
  // 2. dfs for every node
  //    at the end of node, push it to the each component vector
  // 3. if all nodes are marked as visited then return count 
  int test, N, H;
  int i, j, k, m;
  int total;

  cin >> test;

  while (test-- > 0)
  {
    cin >> N;
    cin >> H;
    // reset
    total = 0;
    for (i = 0 ; i < N ; i++) 
    {
      v[i] = 0;
      for (j = 0 ; j < N ; j++)
      {
        g[i][j] = 0;
      }
    }
    // marking
    int first, second;
    for (i = 0 ; i < H ; i++)
    {
      cin >> first;
      cin >> second;
      g[first][second] = 1;
      g[second][first] = 1; 
    }
 
    for (i = 0; i < N; i++) 
    {
      int ret = dfs(i, N, H);
      total += ret;
    }
    cout << total << endl;
  }
  return 0;
}

