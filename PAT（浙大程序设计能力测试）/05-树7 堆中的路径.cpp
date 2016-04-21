#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAX 1001
#define MinNum -10001
#define TURE 1
using namespace std;

typedef int DataType;
typedef struct HeapNode *MinHeap;
struct HeapNode {
  DataType *Elements;
  int size;
  int capacity;
};

bool IsFull(MinHeap H) { return (H->size == H->capacity); }

bool IsEmpty(MinHeap H) { return (H->size == 0); }

MinHeap CreateHeap(int N) {
  MinHeap H = (MinHeap)malloc(sizeof(struct HeapNode));
  H->Elements = (DataType *)malloc((MAX + 1) * sizeof(DataType));
  H->size = 0;
  H->capacity = MAX;
  H->Elements[0] = MinNum; //作为哨兵
  return H;
}

void Insert(MinHeap H, DataType X) {
  if (IsFull(H))
    return;
  int i = ++H->size;
  for (; X <= H->Elements[i / 2]; i = i / 2) {
    H->Elements[i] = H->Elements[i / 2];
  }
  H->Elements[i] = X;
  // return TURE;
}

void PrecDown(MinHeap H, int p) {
  int Parent, Child;
  DataType X;
  X = H->Elements[p]; /* 取出根结点存放的值 */
  for (Parent = p; Parent * 2 <= H->size; Parent = Child) {
    Child = Parent * 2;
    if ((Child != H->size) && (H->Elements[Child] > H->Elements[Child + 1]))
      Child++; /* Child指向左右子结点的较xiao者 */
    if (X <= H->Elements[Child])
      break; /* 找到了合适位置 */
    else     /* 下滤X */
      H->Elements[Parent] = H->Elements[Child];
  }
  H->Elements[Parent] = X;
}

void BuildHeap(MinHeap H) {
  int i;
  for (i = H->size / 2; i > 0; i--) {
    PrecDown(H, i);
  }
}

void PrintHeap(MinHeap H, int M) {
  int i;
  for (i = M; H->Elements[i] != H->Elements[1];) {
    printf("%d ", H->Elements[i]);
    i = i / 2;
  }
}

int main() {
  int i, X, M, N;
  int leaf;
  // int heapNode[MAX];
  scanf("%d %d", &N, &M);
  MinHeap H = CreateHeap(N);
  for (i = 0; i < N; i++) {
    scanf("%d", &X);
    Insert(H, X);
  }
  // BuildHeap(H);
  for (i = 0; i < M; i++) {
    scanf("%d", &leaf);
    printf("%d", H->Elements[leaf]);
    while (leaf > 1) {
      leaf = leaf / 2;
      printf(" %d", H->Elements[leaf]);
    }
    printf("\n");
  }
  return 0;
}
