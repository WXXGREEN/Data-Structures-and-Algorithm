/*拯救007
by zoe */
#include <cmath>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#define YES 1
#define NO 0
using namespace std;
struct Point {
  int num;
  int x;
  int y;
  Point &operator=(Point P) {
    num = P.num;
    x = P.x;
    y = P.y;
    return *this;
  }
};

Point M[102][102];
Point P[102];
bool visited[102];
int nu;
// int ne;
int D;

bool Jump(Point P, Point V) {
  if (sqrt((P.x - V.x) * (P.x - V.x) + (P.y - V.y) * (P.y - V.y)) < D)
    return true;
  else
    return false;
}

bool FirstCanJump(Point P) {
  // printf("judge first can jump:%f\n", sqrt(P.x * P.x + P.y * P.y));
  if (sqrt(P.x * P.x + P.y * P.y) < D)
    return true;
  else
    return false;
}

bool IsSafe(Point P) {
  if (fabs(P.x - 50) < D || fabs(P.y - 50) < D)
    return true;
  else
    return false;
}

int DFS(Point Pv) {
  // printf("DFS start!\n");
  int answer;
  Point V;
  visited[Pv.num] = true;
  if (IsSafe(Pv))
    answer = YES;
  else {
    // printf("not the end\n");
    for (int i = 0; i < nu; i++) {
      V = P[i];
      if (!visited[V.num] && Jump(Pv, V)) {
        answer = DFS(V);
        if (answer == YES)
          break;
      }
    }
  }
  return answer;
}

void Save007(Point Pv) {

  int answer;
  for (int i = 0; i < nu; i++) {
    Pv = P[i];
    if (!visited[Pv.num] && FirstCanJump(Pv)) {
      // printf("first can jump\n");
      answer = DFS(Pv);
      if (answer == YES)
        break;
    }
    // Pv = P[i];
  }
  if (answer == YES)
    printf("Yes\n");
  else
    printf("No\n");
}

int main() {
  int i;

  // string S;

  cin >> nu >> D;
  // cout << nu << " " << D << endl;
  if (nu <= 0)
    printf("No\n");
  for (i = 0; i < nu; i++)
    P[i].num = i;

  for (i = 0; i < nu; i++) {
    scanf("%d%d\n", &P[i].x, &P[i].y);
    // cout << i << endl;
    // cout << i << " " << P[i].x << " " << P[i].y << endl;
  }
  for (i = 0; i < nu; i++)
    visited[i] = 0;

  // cout << 0 << " " << P[0].x << " " << P[0].y << endl;

  Save007(P[0]);
  /*int i, a[6];
  for (i = 0; i < 5; i++)
    cin >> a[i];
  cout << a[4] << endl;*/
  return 0;
}
