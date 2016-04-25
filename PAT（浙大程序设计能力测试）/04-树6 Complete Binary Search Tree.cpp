#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int A[1001], T[1001];

int compare(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int getLeftLength(int N) {
  double H = floor(log2(N + 1));
  // cout << "H:" << H << endl;
  double X = N + 1 - exp2(H);
  // cout << "X:" << X << endl;
  double y = exp2(H - 1);
  // cout << "y:" << y << endl;
  X = X - y > 0 ? y : X;
  int L = exp2(H - 1) - 1 + X;
  return L;
}

void solve(int Aleft, int Aright, int TRoot) {
  int leftRoot, rightRoot;
  int n = Aright - Aleft + 1;
  if (n == 0)
    return;
  // cout << n << endl;
  int L = getLeftLength(n);
  // cout << "L:" << L << endl;
  T[TRoot] = A[Aleft + L];
  leftRoot = TRoot * 2 + 1;
  rightRoot = leftRoot + 1;
  solve(Aleft, Aleft + L - 1, leftRoot);
  solve(Aleft + L + 1, Aright, rightRoot);
}

int main() {
  int N, Aleft, Aright, TRoot;

  scanf("%d", &N);
  for (int i = 0; i < N; i++)
    scanf("%d", &A[i]);

  qsort(A, N, sizeof(int), compare);

  solve(0, N - 1, 0);
  printf("%d", T[0]);
  for (int i = 1; i < N; i++)
    printf(" %d", T[i]);
}
