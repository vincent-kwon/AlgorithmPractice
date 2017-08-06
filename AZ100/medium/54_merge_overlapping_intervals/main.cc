// A C++ program for merging overlapping intervals
#include<bits/stdc++.h>
using namespace std;
 
// An interval has start time and end time
struct Interval
{
    int start, end;
};
 
// Compares two intervals according to their staring time.
// This is needed for sorting the intervals using library
// function std::sort(). See http://goo.gl/iGspV
bool compareInterval(Interval i1, Interval i2)
{
    return (i1.start < i2.start);
}
 
// The main function that takes a set of intervals, merges
// overlapping intervals and prints the result
void mergeIntervals(Interval arr[], int n)
{
    // Test if the given set has at least one interval
    if (n <= 0) // MEMO : corner case
        return;
 
    // Create an empty stack of intervals
    stack<Interval> s; // MEMO: Wow, struct for template
 
    // sort the intervals in increasing order of start time
    sort(arr, arr+n, compareInterval); // MEMO: Wow, just array and arr+n
 
    // push the first interval to stack
    s.push(arr[0]); // MEMO: initial one
 
    // Start from the next interval and merge if necessary
    for (int i = 1 ; i < n; i++)
    {
        // get interval from stack top
        Interval top = s.top();
 
        // if current interval is not overlapping with stack top,
        // push it to the stack
        if (top.end < arr[i].start)
            s.push(arr[i]);
 
        // Otherwise update the ending time of top if ending of current
        // interval is more
        else if (top.end < arr[i].end)
        {
            top.end = arr[i].end;
            s.pop();
            s.push(top);
        }
    }
 
    // Print contents of stack
    cout << "\n The Merged Intervals are: ";
    while (!s.empty())
    {
        Interval t = s.top();
        cout << "[" << t.start << "," << t.end << "] ";
        s.pop();
    }
    return;
}
 
// Driver program
int main()
{
    Interval arr[] =  { {6,8}, {1,9}, {2,4}, {4,7} }; // MEMO: wow struct initialization really easy
    int n = sizeof(arr)/sizeof(arr[0]); // MEMO: size of array
    mergeIntervals(arr, n); // MEMO: passing arr[] just 
    return 0;
}
