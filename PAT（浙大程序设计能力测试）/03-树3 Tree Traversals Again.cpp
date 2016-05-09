#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#define MAX 31
int Pre[MAX], In[MAX], Post[MAX], A[MAX];
// void Change(int Pre[MAX], int In[MAX]);
void Solve(int preL, int inL, int postL, int n);

int main() {

  int n, x, i = 0, j = 0, cnt = 0;
  string s;
  cin >> n;
  while (cin >> s >> x) {
    if (s == "Push") {
      Pre[i++] = x;
      cnt++;
    } else {
      In[j++] = Pre[cnt--];
    }
  }
  for (int i = 0; i < n; i++)
    cout << In[i] << " ";
}

void Solve(int preL, int inL, int postL, int n) {
  int root, L, R;
  if (n == 0)
    return;
  if (n == 1) {
    Post[postL] = Pre[preL];
    return;
  }
  root = Pre[preL];
  Post[posL + n - 1] = root;
  for (int i = 0; i < n; i++) {
    if (In[inL + i] == root)
      break;
  }
  L = i;
  R = n - L - 1;
  Solve(preL + 1, inL, posL, L);
  Solve(preL + L + 1, inL + L, postL + L, R);
}
