#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MIN(a,b) ((a)<=(b)?(a):(b))

#define INT_MIN (1<<31)
#define INT_MAX (((unsigned)INT_MIN) - 1)

#define SET_BIT(i,b) (i |= (1 << b))
#define UNSET_BIT(i,b) (i &= ~(1 << b))
#define GET_BIT(i,b) (((i & 1 << b)>0)?1:0)
#define TOGGLE_BIT(i,b) ((GET_BIT(i,b)==0)?SET_BIT(i,b):UNSET_BIT(i,b))

int g[26][26] = {0, };
char r[100][10];

void dfs(int p, int w, int* inNum, int* outNum, int& v)
{
  inNum[p] += w;
  if (GET_BIT(v, p))  return; 
  SET_BIT(v,p);
  
  for (int i = 0 ; i < 26; i++) 
  {
    if (g[p][i] > 0)
    {
      outNum[p] += g[p][i];
      //cout << "out: " << p << "," << i << "=" << g[p][i] << endl;
      dfs(i, g[p][i], inNum, outNum, v);
    }
  }
}

int main() 
{
  int test;
  cin >> test;
  while (test-- > 0) 
  {
    int N; // 1 <= N <= 100
    int i,j,k,h;
    cin >> N;
    char w[100][10]; // 2 <= size <= 10
    int inNum[26] = {0,};
    int outNum[26] = {0, };

    for (i=0; i < N; i++) cin >> w[i];

    // make graph
    int startPos;

    for (i = 0; i < N; i++) 
    {
      int s, l, c;
      s = w[i][0] - 'a';
      l = strlen(w[i]);
      c = w[i][l-1] - 'a';

      for (j = 0; j < N; j++) 
      {
        if (i == j) continue;
        int r;
        r = w[j][0] -  'a';
        if (c == r) {
          g[s][r]++;
          cout << "match " << s << "," << r << " = " << g[s][r] << endl;
          startPos = s;
          break;
        }
      }
    }
 
    int visited = 0;
    dfs(startPos, 0, inNum, outNum, visited);
    int isEurerCircuit = true;
    
    for (i = 0 ; i < 26; i++) 
    {
      if (inNum[i] != outNum[i]) 
      {
        isEurerCircuit = false;
        break;
      }
    }
 
    if (isEurerCircuit) cout << "Yes, eurer circuit "  << endl;
    else cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
