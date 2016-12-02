#include <iostream>

using namespace std;

#define VC_MAX  987654321
#define VC_MIN -987654321
#define VC_INVALID -1

#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)

#define MAX_N 25

int test, N;
int t1_sr, t1_sc, t1_dr, t1_dc; 
int t2_sr, t2_sc, t2_dr, t2_dc;
int Map[MAX_N][MAX_N];

int Dp[MAX_N][MAX_N][MAX_N][MAX_N]; 

typedef struct {
  int t1_r;
  int t1_c;
  int t2_r;
  int t2_c;
  int t1_dist;
  int t2_dist;
} NodeInfo;

int head = -1;
int tail = -1;

#define MAX_QUEUE 100000
NodeInfo queueArr[MAX_QUEUE];

int move[9][2] = {
  { 0,0 },
  {-1,0 }, 
  {-1,1 },
  { 0,1 },
  { 1,1 },
  { 1,0 },
  { 1,-1},
  { 0,-1},
  {-1,-1} 
};

int bfsDouble() {
  int ret;

  NodeInfo initNode;
  initNode.t1_r = t1_sr;
  initNode.t1_c = t1_sc;
  initNode.t2_r = t2_sr;
  initNode.t2_c = t2_sc;
  initNode.t1_dist = 0;
  initNode.t2_dist = 0;
  
  queueArr[++tail] = initNode;

  while (head != tail) {
    NodeInfo nextInfo = queueArr[++head];
    if (head == MAX_QUEUE) {
      head = -1;
    }
   
    if (nextInfo.t1_r == t1_dr && 
        nextInfo.t1_c == t1_dc &&
        nextInfo.t2_r == t2_dr &&
        nextInfo.t2_c == t2_dc) {
      return (nextInfo.t1_dist > nextInfo.t2_dist ? nextInfo.t1_dist : nextInfo.t2_dist);
    } else {
      //cout << nextInfo.t1_r << " " << nextInfo.t1_c << " , " << nextInfo.t2_r << " " << nextInfo.t2_c << endl;
    }    

    int new_t1_r;
    int new_t1_c;
    int new_t2_r;
    int new_t2_c;
    int new_t1_dist;
    int new_t2_dist;

    for (int i = 0; i < 9; i++) {
      if (!(nextInfo.t1_r == t1_dr && nextInfo.t1_c == t1_dc)) {
        new_t1_r = nextInfo.t1_r + move[i][0];
        new_t1_c = nextInfo.t1_c + move[i][1];
        new_t1_dist = nextInfo.t1_dist + 1;
      }
      else {
        new_t1_r = nextInfo.t1_r;
        new_t1_c = nextInfo.t1_c;
        new_t1_dist = nextInfo.t1_dist;
      }
 
      if (new_t1_r < 0 || new_t1_c < 0) continue;
      if (new_t1_r >= N || new_t1_c >= N) {
        continue;
      }
 

      if (Map[new_t1_r][new_t1_c] == 0) { 

        for (int k = 0; k < 9; k++) {
          if (!(nextInfo.t2_r == t2_dr && nextInfo.t2_c == t2_dc)) {
            new_t2_r = nextInfo.t2_r + move[k][0];
            new_t2_c = nextInfo.t2_c + move[k][1];
            new_t2_dist = nextInfo.t2_dist + 1;
          }
          else {
            new_t2_r = nextInfo.t2_r;
            new_t2_c = nextInfo.t2_c;
            new_t2_dist = nextInfo.t2_dist;
          }

          if (new_t2_r < 0 || new_t2_c < 0) continue;
          if (new_t2_r >= N || new_t2_c >= N) {
            continue;
          }
          
          if (Map[new_t2_r][new_t2_c] == 0) {

            if (Dp[new_t1_r][new_t1_c][new_t2_r][new_t2_c] == 1) continue;

	    int bigger_r = (new_t1_r > new_t2_r) ? new_t1_r : new_t2_r;
            int bigger_c = (new_t1_c > new_t2_c) ? new_t1_c : new_t2_c;
            int small_r = (new_t1_r < new_t2_r) ? new_t1_r : new_t2_r;
            int small_c = (new_t1_c < new_t2_c) ? new_t1_c : new_t2_c;

            if (((bigger_r - small_r) <= 1) && ((bigger_c - small_c) <= 1)) continue;
            
	    NodeInfo newInfo;
            newInfo.t1_r = new_t1_r;
            newInfo.t1_c = new_t1_c;
            newInfo.t2_r = new_t2_r;
            newInfo.t2_c = new_t2_c;
            newInfo.t1_dist = new_t1_dist;
            newInfo.t2_dist = new_t2_dist;
            
            if (tail == (MAX_QUEUE-1)) {
              tail = -1;
            }
	    queueArr[++tail] = newInfo;
            Dp[new_t1_r][new_t1_c][new_t2_r][new_t2_c] = 1;
          }  
        }
      }
    }
  }
  return ret;
}

int main() {
  cin >> test;

  while (test--) {
    cin >> N;

    for (int i = 0; i < MAX_N; i++) 
      for (int i2 = 0; i2 < MAX_N; i2++)
        for (int i3 = 0; i3 < MAX_N; i3++)
          for (int i4 = 0; i4 < MAX_N; i4++)
            Dp[i][i2][i3][i4] = 0;

    cin >> t1_sr;
    cin >> t1_sc;
    cin >> t1_dr;
    cin >> t1_dc;

    cin >> t2_sr;
    cin >> t2_sc;
    cin >> t2_dr;
    cin >> t2_dc;

    t1_sr--;
    t1_sc--;
    t1_dr--;
    t1_dc--;

    t2_sr--;
    t2_sc--;
    t2_dr--;
    t2_dc--;

    for (int i = 0; i < N; i++) {
      for (int k = 0; k < N; k++) {
        cin >> Map[i][k];  
      }
    }

    int ret = bfsDouble();
    cout << "r: " << ret << endl;
  }
  return 0;
}
