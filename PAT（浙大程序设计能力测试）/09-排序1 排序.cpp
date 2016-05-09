#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;
typedef int ElementType;
int cutOff;

void InsertionSort(ElementType A[], int N) { /* 插入排序 */
  int P, i;
  ElementType Tmp;

  for (P = 1; P < N; P++) {
    Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
    for (i = P; i > 0 && A[i - 1] > Tmp; i--)
      A[i] = A[i - 1]; /*依次与已排序序列中元素比较并右移*/
    A[i] = Tmp;        /* 放进合适的位置 */
  }
}

void ShellSort0(ElementType A[], int N) {
  int i, P, D, temp;
  for (D = N / 2; D > 0; D /= 2) {
    for (P = D; P < N; P++) {
      temp = A[P];
      for (i = P; i >= D && A[i - D] > temp; i -= D)
        A[i] = A[i - D];
      A[i] = temp;
    }
  }
}

void ShellSort1(ElementType A[], int N) { /* 希尔排序 - 用Sedgewick增量序列 */
  int Si, D, P, i;
  ElementType Tmp;
  /* 这里只列出一小部分增量 */
  int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

  for (Si = 0; Sedgewick[Si] >= N; Si++)
    ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */

  for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
    for (P = D; P < N; P++) { /* 插入排序*/
      Tmp = A[P];
      for (i = P; i >= D && A[i - D] > Tmp; i -= D)
        A[i] = A[i - D];
      A[i] = Tmp;
    }
}

void Swap(ElementType *a, ElementType *b) {
  ElementType t = *a;
  *a = *b;
  *b = t;
}

void PercDown(ElementType A[], int p,
              int N) { /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
  /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
  int Parent, Child;
  ElementType X;

  X = A[p]; /* 取出根结点存放的值 */
  for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
    Child = Parent * 2 + 1;
    if ((Child != N - 1) && (A[Child] < A[Child + 1]))
      Child++; /* Child指向左右子结点的较大者 */
    if (X >= A[Child])
      break; /* 找到了合适位置 */
    else     /* 下滤X */
      A[Parent] = A[Child];
  }
  A[Parent] = X;
}

void HeapSort(ElementType A[], int N) { /* 堆排序 */
  int i;

  for (i = N / 2 - 1; i >= 0; i--) /* 建立最大堆 */
    PercDown(A, i, N);

  for (i = N - 1; i > 0; i--) {
    /* 删除最大堆顶 */
    Swap(&A[0], &A[i]); /* 见代码7.1 */
    PercDown(A, 0, i);
  }
}

/* 归并排序 - 递归实现 */

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(
    ElementType A[], ElementType TmpA[], int L, int R,
    int RightEnd) { /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
                       */
  int LeftEnd, NumElements, Tmp;
  int i;

  LeftEnd = R - 1; /* 左边终点位置 */
  Tmp = L;         /* 有序序列的起始位置 */
  NumElements = RightEnd - L + 1;

  while (L <= LeftEnd && R <= RightEnd) {
    if (A[L] <= A[R])
      TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
    else
      TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
  }

  while (L <= LeftEnd)
    TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
  while (R <= RightEnd)
    TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */

  for (i = 0; i < NumElements; i++, RightEnd--)
    A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}

void Msort(ElementType A[], ElementType TmpA[], int L,
           int RightEnd) { /* 核心递归排序函数 */
  int Center;

  if (L < RightEnd) {
    Center = (L + RightEnd) / 2;
    Msort(A, TmpA, L, Center);               /* 递归解决左边 */
    Msort(A, TmpA, Center + 1, RightEnd);    /* 递归解决右边 */
    Merge(A, TmpA, L, Center + 1, RightEnd); /* 合并两段有序序列 */
  }
}

void MergeSort(ElementType A[], int N) { /* 归并排序 */
  ElementType *TmpA;
  TmpA = (ElementType *)malloc(N * sizeof(ElementType));

  if (TmpA != NULL) {
    Msort(A, TmpA, 0, N - 1);
    free(TmpA);
  } else
    printf("空间不足");
}

/*快速排序*/
ElementType Median(ElementType A[], int left, int right) {
  int center = (left + right) / 2;
  if (center < left)
    Swap(&center, &left);
  if (left > right)
    Swap(&left, &right);
  if (center > right)
    Swap(&center, &right);
  Swap(&center, &A[right - 1]);
  return A[right - 1];
}

void quick_sort(ElementType A[], int left, int right) {
  int low, high, pivot;
  if (cutOff <= right - left) {
    pivot = Median(A, left, right);
    low = left;
    high = right - 1;
    while (1) {
      while (A[++low] < pivot) {
      }
      while (A[--high] > pivot) {
      }
      if (low < high)
        Swap(&A[low], &A[high]);
      else
        break;
    }
    Swap(&pivot, &A[low]);
    quick_sort(A, left, low - 1);
    quick_sort(A, low + 1, right);
  } else
    InsertionSort(A + left, right - left + 1);
}

void QuickSort(ElementType A[], int N) { quick_sort(A, 0, N - 1); }

int main() {
  ElementType A[100001], N;
  clock_t start, finish;
  cin >> N;
  cutOff = N;
  for (int i = 0; i < N; i++)
    cin >> A[i];
  start = clock();
  QuickSort(A, N);
  finish = clock();
  double duration = (finish - start) / CLOCKS_PER_SEC;
  // cout << "cost time: " << duration << "s" << endl;
  cout << A[0];
  for (int i = 1; i < N; i++)
    cout << " " << A[i];
  // cout << endl;
}
