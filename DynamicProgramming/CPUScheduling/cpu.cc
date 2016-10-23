/*
 * =====================================================================================
 *
 *       Filename:  cpu.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 10월 22일 05시 32분 06초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define MAX_CPU 3 
#define MAX_PACKET 5 
#define MAX_LENGTH 10

/*   1 2 3 4 5 6 7 8 9 10 11 12
 * 1 * * * * - - - - - -  - - -
 * 2         * * * * * 
 * 3   *(cpu2)
 * 4     . . . . . . . * * * (packet 3 ends cpu0, 12)
 * 5     . . . . . . . . (packet 4 ends cpu1, 11)
 */
int input[5][2] = {
  {1, 4},
  {1, 5},
  {2, 1},
  {3, 3},
  {3, 8}
};

// packet[X][3][4][0][0][0][0]
//
int memo[MAX_PACKET][10][10][10] = { 0, };

// cpu[0] 
// cpu[1]
// cpu[2]
// cpu[3]
// cpu[4]
bool isTurnedOn(int status, int cpuNo) {
  int mask = 1 << cpuNo;
  status = status & mask;
  if (status != 0) return true;
  else return false;
}

void turnOn(int& status, int cpuNo) {
  int mask = 1 << cpuNo;
  status = status | mask; 
  //cout << "turn on " << status << ", " << cpuNo << endl;
}

int getCPUCount(int status) {
  int count = 0;
  //cout << "getCputCount: " << status << endl;
  for (int i = 0 ; i < MAX_CPU; i++) {
    if (isTurnedOn(status, i)) count++;
  }
  //cout << "finishCount: " << count << endl;
  return count;
}

int getEndTime(int packet, int cpu, map<int, vector<std::pair<int, int>> > & mmap) {
  int newEnterTime = input[packet][0];
  int newDuration = input[packet][1];

  if (mmap[cpu].size() == 0) return newEnterTime + newDuration;
  
  int oldFinishTime = mmap[cpu].back().second;
  //cout << " oldFinish: " << oldFinishTime << endl;

  if (oldFinishTime <= newEnterTime) return newEnterTime + newDuration;
  else return (oldFinishTime + newDuration);   
}

bool addPacket(int packet, int cpu, int status, map<int, vector<std::pair<int, int>> >& mmap) {
  if (!isTurnedOn(status, cpu)) return false;
  
  int newEndTime = getEndTime(packet, cpu, mmap);

  int latency = newEndTime - input[packet][0]; // enter time

  if (latency > MAX_LENGTH) return false;
  else {
    cout << "alloc: packet:" << packet << ",cpu:" << cpu << ", end:" << newEndTime << ", cnt: " << getCPUCount(status) << endl;
    mmap[cpu].push_back(make_pair(input[packet][0], newEndTime));
    return true;
  }
}

int getRemaining(int packet, int cpu, map<int, vector<std::pair<int, int>> >& mmap) {
  if (mmap[cpu].size() == 0) return 0;

  else {
    int endTime = mmap[cpu].back().second;
    int currentTime = input[packet][0];
    if (endTime <= currentTime) return 0;
    else return (endTime - currentTime);
  }
}

int getMinCpu(int packet, int cpuStatus, map<int, vector<std::pair<int, int>> >& mmap) {
  if (packet == MAX_PACKET) {
    //cout << "end here " << getCPUCount(cpuStatus) << endl;
    return getCPUCount(cpuStatus);
  }
  int r = MAX_CPU+1;
  bool allocNew = false;
 
  //cout << packet << "," << endl; 
  
  cout << "****** start memo ******* " << endl;
  int cpu0 = getRemaining(packet, 0, mmap);
  int cpu1 = getRemaining(packet, 1, mmap);
  int cpu2 = getRemaining(packet, 2, mmap);
  
  if (memo[packet][cpu0][cpu1][cpu2] != 0) {
    cout << "Memoed : " << memo[packet][cpu0][cpu1][cpu2] << endl;
    return memo[packet][cpu0][cpu1][cpu2];
  }
  cout << packet <<endl;
  cout << cpu0 <<endl;
  cout << cpu1 <<endl;
  cout << cpu2 <<endl;
  cout << "****** end memo ******* " << endl;
  
  for (int i = 0; i < MAX_CPU; i++) {
    int updatedCpuStatus = cpuStatus;
    bool popNeeded = false;

    if (!isTurnedOn(updatedCpuStatus, i) && !allocNew) { // alloc only once
      turnOn(updatedCpuStatus, i); // this is enabling of temporary value so don't worry
      addPacket(packet, i, updatedCpuStatus, mmap);
      popNeeded = true;
      allocNew = true;
      r = min(r, getMinCpu(packet+1, updatedCpuStatus, mmap));
    }  
    else if (isTurnedOn(updatedCpuStatus, i)) {
      if (addPacket(packet, i, updatedCpuStatus, mmap)) {
        popNeeded = true;
        r = min(r, getMinCpu(packet+1, updatedCpuStatus, mmap));
      }
    }

    if (popNeeded) mmap[i].pop_back();
  } 
 
   
  memo[packet][cpu0][cpu1][cpu2] = r;
  return r; 
}

int main() {
  map<int, vector<std::pair<int,int>>> mmap;
  for (int i = 0; i < MAX_CPU; i++) {
    vector<std::pair<int, int> > v;
    mmap[i] = v; // add empty
  }
  int r = getMinCpu(0, 0, mmap);
  cout << "Finished..." << endl;
  cout << r << endl;
}
