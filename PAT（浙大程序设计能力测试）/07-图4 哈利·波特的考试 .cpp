#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define MaxNum 101
#define INFINITY 10000

typedef struct GNode *MGraph;
struct GNode {
  int Nv;
  int Ne;
  int weight[MaxNum][MaxNum];
};

typedef struct ENode *Edge;
struct ENode {
  int W;
  int V;
  int weight;
};

MGraph CreateGraph(int verNum) {
  // cout << "create " << endl;
  MGraph G;
  G = (MGraph)malloc(sizeof(struct GNode));
  G->Nv = verNum;
  G->Ne = 0;
  for (int i = 0; i < verNum; i++) {
    for (int j = 0; j < verNum; j++)
      G->weight[i][j] = INFINITY;
  }

  return G;
}

MGraph InsertEdge(MGraph G, Edge E) {
  G->weight[E->V][E->W] = E->weight;
  G->weight[E->W][E->V] = E->weight;
  return G;
}

MGraph BuildGraph() {
  int verNum, EdgeNum;
  Edge E;
  cin >> verNum >> EdgeNum;
  if (verNum == 0)
    cout << 0 << endl;
  else {
    // cout << "CreateGraph " << endl;
    MGraph G = CreateGraph(verNum);
    // cout << G->Nv << endl;
    G->Ne = EdgeNum;
    if (G->Ne != 0) {
      for (int i = 0; i < EdgeNum; i++) {
        // cout << " not yet" << endl;
        E = (Edge)malloc(sizeof(struct ENode));
        cin >> E->V >> E->W >> E->weight;
        E->V--;
        E->W--;
        G = InsertEdge(G, E);
      }

      return G;
    } else
      cout << 0 << endl;
  }
}

void floyd(MGraph G, int D[][MaxNum]) {
  // cout << "in floyd Nv: " << G->Nv << endl;
  int cnt = 0;
  /*for (int i = 0; i < G->Nv; i++) {
    for (int j = 0; i < G->Nv; j++) {
      D[i][j] = G->weight[i][j];
      cout << cnt++ << endl;
    }
  }*/
  for (int i = 0; i < G->Nv; i++) {
    for (int j = 0; j < G->Nv; j++) {
      // cout << cnt++ << endl;
      D[i][j] = G->weight[i][j];
    }
  }
  // cout << "floyd " << endl;
  for (int k = 0; k < G->Nv; k++) {
    for (int i = 0; i < G->Nv; i++) {
      for (int j = 0; j < G->Nv; j++) {
        if (D[i][k] + D[k][j] < D[i][j]) {
          D[i][j] = D[i][k] + D[k][j];
          // cout << "floyd " << endl;
        }
      }
    }
  }
  // cout << "floyd " << endl;
}

int FindMax(int D[][MaxNum], int i, int N) {
  int j, MaxDis = 0;
  for (j = 0; j < N; j++) {
    if (j != i && D[i][j] > MaxDis)
      MaxDis = D[i][j];
  }
  return MaxDis;
}

void FindAnimal(MGraph G) {
  // cout << "find animal" << endl;
  int D[MaxNum][MaxNum];
  int MaxNode, MinNode, Animal = 0;
  MinNode = INFINITY;
  // cout << "folyd" << endl;
  floyd(G, D);
  for (int i = 0; i < G->Nv; i++) {
    // cout << "find max" << endl;
    MaxNode = FindMax(D, i, G->Nv);
    if (MaxNode == INFINITY) {
      cout << endl;
      return;
    }
    if (MaxNode < MinNode) {
      MinNode = MaxNode;
      Animal = i + 1;
    }
  }
  cout << Animal << " " << MinNode << endl;
}

int main() {
  MGraph G = BuildGraph();

  FindAnimal(G);
}
