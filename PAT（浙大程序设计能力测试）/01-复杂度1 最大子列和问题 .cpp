#include <iostream>
#include <stack>
#include <time.h>
#define MAX 100001

using namespace std;

int MaxSubseqSum4(int A[], int N) {
  int ThisSum = 0, MaxSum = 0;
  for (int i = 0; i < N; i++) {
    ThisSum += A[i];
    if (ThisSum > MaxSum)
      MaxSum = ThisSum;
    else if (ThisSum < 0)
      ThisSum = 0;
  }
  return MaxSum;
}

int main() {
  int A[MAX];
  int x, N, i;
  cin >> N;
  for (i = 0; i < N; i++) {
    cin >> A[i];
  }
  int MaxSum = MaxSubseqSum4(A, N);
  cout << MaxSum << endl;
}
