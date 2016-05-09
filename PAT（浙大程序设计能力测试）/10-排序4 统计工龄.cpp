
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <time.h>
#include <vector>

using namespace std;
typedef int ElementType;

int main() {
  int i, N, year;
  vector<int> vec;
  cin >> N;
  i = N;
  while (i > 0) {
    cin >> year;
    vec.push_back(year);
    --i;
  }
  // cout << "begin" << endl;
  map<int, size_t> work_year;
  for (int j = 0; j < N; j++) {
    work_year[vec[j]]++;
  }
  sort(vec.begin(), vec.end());
  //删除相邻的重复元素
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  for (size_t j = 0; j < vec.size(); j++) {
    cout << vec[j] << ":" << work_year[vec[j]] << endl;
  }
}
