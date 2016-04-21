#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

//定义平衡二叉树
typedef int DataType;
typedef struct AVLNode *position;
typedef position AVLTree;
typedef struct AVLNode {
  DataType data;
  AVLTree left;
  AVLTree right;
  int Height;
};

//读入数据，建立平衡二叉树
int Max(int a, int b) { return a > b ? a : b; }

int GetHeight(AVLTree T) {
  int LH, RH, MAXH;
  if (T) {
    LH = GetHeight(T->left);
    RH = GetHeight(T->right);
    MAXH = LH > RH ? LH : RH;
    return MAXH + 1;
  } else
    return 0;
}

AVLTree SingleLeftRotation(AVLTree T) {
  AVLTree B;
  B = T->left;
  T->left = B->right;
  B->right = T;
  T->Height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;
  B->Height = Max(GetHeight(B->left), T->Height) + 1;
  return B;
}

AVLTree SingleRightRotation(AVLTree T) {
  AVLTree C;
  C = T->right;
  T->right = C->left;
  C->left = T;
  T->Height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;
  C->Height = Max(GetHeight(T->left), T->Height) + 1;
  return C;
}

AVLTree DoubelLeftRightRotation(AVLTree A) {
  A->left = SingleRightRotation(A->left);
  return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A) {
  A->right = SingleLeftRotation(A->right);
  return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, DataType X) {
  if (!T) {
    T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->data = X;
    T->left = T->right = NULL;
    T->Height = 0;
  } else if (X < T->data) {
    T->left = Insert(T->left, X);
    if (GetHeight(T->left) - GetHeight(T->right) == 2) {
      if (X < T->left->data)
        T = SingleLeftRotation(T);
      else
        T = DoubelLeftRightRotation(T);
    }
  } else if (X > T->data) {
    T->right = Insert(T->right, X);
    if (GetHeight(T->right) - GetHeight(T->right) == -2) {
      if (X > T->right->data)
        T = SingleRightRotation(T);
      else
        T = DoubleRightLeftRotation(T);
    }
  }
  T->Height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;
  return T;
}

void PreOrderPrintTree(AVLTree T) {
  if (!T)
    return;
  printf("%d  ", T->data);
  PreOrderPrintTree(T->left);
  PreOrderPrintTree(T->right);
}

int main() {
  int i, N, num[22];
  scanf("%d\n", &N);
  AVLTree T = NULL;

  for (i = 0; i < N; i++) {
    cin >> num[i];
    // printf("built avltree !\n");

    // PreOrderPrintTree(T);
    // printf("\n");
  }
  for (i = 0; i < N; i++)
    T = Insert(T, num[i]);

  printf("%d  \n", T->data);

  return 0;
}
