// 21:10

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define INT_MIN (1<<31)
#define INT_MAX (((unsignd int)INT_MIN)-1)
#define MIN(a,b) ((a)<=(b)?(a):(b))

#define SET_BIT(a,b) ((a) |= (1<<(b)))
#define GET_BIT(a,b) (((a) & (1<<(b)))>0?1:0)
#define CLEAR_BIT(a,b) ((a) &= ~(1<<(b)))
#define TOGGLE_BIT(a,b) if (GET_BIT(a,b) == 1) CLEAR_BIT(a,b); \
                        else \
			SET_BIT(a,b);

char w[200][20]; //is this best?
int a[26][26] = {0, };
int r[26]; // how to keep alphabet char sort 
int r_len = 0;

void dfs(int p, int& visited)
{
  if (visited & (1 << p))
    return;

  visited |= (1 << p);

  for (int i = 0 ; i < 26; i++) 
  {
    if (a[p][i] == 1)
      dfs(i, visited);
  }
  r[r_len++] = p; 
}

int main() 
{
  int test, words;
  int t = 0;
  SET_BIT(t,1);
  SET_BIT(t,2);
  cout << t << endl;
  TOGGLE_BIT(t, 1);
  TOGGLE_BIT(t, 0);
  cout << t << endl;

  cin >> test;

  while (test-- > 0) 
  {
    int i = 0;
    r_len = 0; // result index
    int w_num;
    cin >> w_num;

    // clean up every things
    for (i = 0 ; i < 26; i++) 
      for (int j = 0 ; j < 26; j++)
        a[i][j] = 0;


    for (int z = 0 ; z < w_num; z++)
    {
      cin >> w[z];
    }

    int candidate = 0;

    for (i = 1; i < w_num ; i++)  
    {
      int prev = i - 1;
      int first_len = strlen(w[prev]);
      int second_len = strlen(w[i]);
      int smaller_len = MIN(first_len, second_len);
      int j = 0;

      for (j; j < smaller_len; j++) 
      {
        if (w[prev][j] == w[i][j]) 
          continue;
        else 
        {
          int tobefore = w[prev][j] - 'a';
          int toafter = w[i][j] - 'a';
          a[tobefore][toafter] = 1; 
          SET_BIT(candidate, tobefore);
          break;
        }
      }
    } 
    // 2. DFS
    int visited = 0;
    int k;

    for (i = 0; i < 26; i++) 
    {
      if (GET_BIT(candidate, i))
        dfs(i, visited);
    }

    // 3. if no more to go, save it in result
    // 4. do it until DFS ends (all traversed)
    // 5. reverse result (left is eariler)
    for (i = 0, k = r_len - 1; i < k; i++, k--) 
    {
      int temp = r[i];
      r[i] = r[k];
      r[k] = temp;
    }

    // 6. check cycle b --> a exists or not
    bool isCycle = false;

    for (i = 0; i < r_len ; i++) 
    {
      for (k = i+1 ; k < r_len; k++) 
      {
        if (a[k][i] == 1)
        {
          isCycle = true;
          break;   
        }
      }    
      if (isCycle) break;
    }

    // 7. after writing all other should follow
    if (isCycle) cout << "INVALID HYPOTHESIS" << endl;
    else 
    {
      int alphabet = 0;
      for (i = 0 ; i < r_len ; i++) 
      {
        cout << (char)(r[i] + 'a');
        SET_BIT(alphabet, r[i]);
      }
      for (i = 0 ; i < 26; i++) 
      {
        if (GET_BIT(alphabet,i) == 0)
        {
          cout << ((char)(i + 'a'));
        }
      }
    }
    cout << "" << endl;
  }
  return 0;
}
