#include <iostream>
#include <stack>
#include <time.h>
#include <vector>
#define MAX 100001
using namespace std;
int p = 0, q = 0;
/*算法二：蛮力法的改进，每次循环一遍不用从头开始加,时间复杂度O(N^2)*/
int MaxSubseqSum2(int A[], int N) {
  int ThisSum, MaxSum = 0;

  for (int i = 0; i < N; i++) {
    ThisSum = 0;
    // p = i;
    for (int j = i; j < N; j++) {
      ThisSum += A[j]; //加一项即可
      if (ThisSum > MaxSum) {
        MaxSum = ThisSum;
        p = i;
        q = j;
      }
    }
  }
  return MaxSum;
}
int main() {
  int A[MAX], MaxSum = 0;
  int x, N, i, j = 0;
  cin >> N;
  for (i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (i = 0; i < N; i++) {
    if (A[i] < 0)
      j++;
  }
  if (j == N) {
    MaxSum = 0;
    p = 0, q = N;
    cout << MaxSum << " " << p << " " << q << endl;
  } else {
    MaxSum = MaxSubseqSum2(A, N);
    cout << MaxSum << " " << p << " " << q << endl;
  }
}
