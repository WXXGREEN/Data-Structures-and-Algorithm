#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef struct Node *Vertex;

//邻接链表表示图
struct Node {
  int data;
  vector<int> edge;
};

Vertex *vertexs;
bool visited[10];
vector<int> temp;

void printArray(vector<int> a) {
  printf("{ ");
  for (unsigned i = 0; i < a.size(); i++)
    printf("%d ", a[i]);
  printf("}\n");
}

void initvisited(bool a[]) {
  for (int i = 0; i < 10; i++)
    a[i] = false;
}

void Visit(int x) { temp.push_back(x); }

void DFS(Vertex V) {
  Visit(V->data);
  visited[V->data] = true;
  for (unsigned i = 0; i < V->edge.size(); i++)
    if (!visited[vertexs[V->edge[i]]->data])
      DFS(vertexs[V->edge[i]]);
}

void BFS(Vertex V) {
  queue<Vertex> Q;
  Q.push(V);
  visited[V->data] = true;
  while (!Q.empty()) {
    Vertex x = Q.front();
    Q.pop();
    Visit(x->data);
    for (unsigned i = 0; i < x->edge.size(); i++) {
      if (!visited[x->edge[i]]) {
        visited[x->edge[i]] = true;
        Q.push(vertexs[x->edge[i]]);
      }
    }
  }
}

void ListComponents(int n) {
  for (int i = 0; i < n; i++) {
    if (!visited[vertexs[i]->data]) {
      DFS(vertexs[i]);
      printArray(temp);
      temp.clear();
    }
  }
  initvisited(visited);
  for (int i = 0; i < n; i++) {
    if (!visited[vertexs[i]->data]) {
      BFS(vertexs[i]);
      printArray(temp);
      temp.clear();
    }
  }
}

int main() {
  int n, e;
  cin >> n >> e;
  vertexs = new Vertex[n];
  for (int i = 0; i < n; i++) {
    vertexs[i] = new Node;
    vertexs[i]->data = i;
  }
  for (int i = 0; i < e; i++) {
    int x, y;
    cin >> x >> y;
    vertexs[x]->edge.push_back(y);
    sort(vertexs[x]->edge.begin(), vertexs[x]->edge.end());
    vertexs[y]->edge.push_back(x);
    sort(vertexs[y]->edge.begin(), vertexs[y]->edge.end());
  }
  initvisited(visited);
  ListComponents(n);
  return 0;
}
