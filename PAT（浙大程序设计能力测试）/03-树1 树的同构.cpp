#include <stdio.h>
#include <stdlib.h>

//-------------二叉树的表示
/*因为题目中的树的结点是编号，所以这里采用静态链表的形式*/
#define MaxTree 10
#define Null -1
typedef int Tree;
typedef char Type;

struct TreeNode {
  Type element;
  Tree left;
  Tree right;
} T1[MaxTree], T2[MaxTree];
//-------------二叉树的建立
Tree ReadTree(struct TreeNode T[]) {
  int i, N;
  Tree Root;
  char left, right;
  scanf("%d", &N);
  int check[N];
  for (i = 0; i < N; i++)
    check[i] = 0;
  if (N) {
    for (i = 0; i < N; i++) {
      scanf("%c%c%c\n", &T[i].element, &left, &right);
    }
    if (left != '-') {
      T[i].left = left - '0';
      check[T[i].left] = 1;
    } else
      T[i].left = Null;

    if (right != '-') {
      T[i].right = right - '0';
      check[T[i].right] = 1;
    } else
      T[i].right = Null;
    for (i = 0; i < N; i++) {
      if (!check[i])
        break;
    }
    Root = i;
  }

  return Root;
}

//-------------同构判别
int isomophic(Tree x1, Tree x2) {

  if (x1 == Null && x2 == Null)
    return 1;
  if ((x1 == Null && x2 != Null) || (x1 != Null && x2 == Null))
    return 0;
  if (T1[x1].element != T2[x2].element)
    return 0;
  if (T1[x1].left == Null && T2[x2].left == Null)
    isomophic(T1[x1].right, T2[x2].right);
  if ((T1[x1].left != Null && T2[x1].left != Null) &&
      (T1[T1[x1].left].element == T2[T2[x2].right].element)) {
    return (isomophic(T1[x1].left, T2[x2].left) &&
            isomophic(T1[x1].right, T2[x2].right));
  } else {
    return (isomophic(T1[x1].left, T2[x1].right) &&
            isomophic(T1[x1].right, T2[x2].left));
  }
}

int main() {
  Tree R1, R2;
  R1 = ReadTree(T1);
  R2 = ReadTree(T2);
  if (isomophic(R1, R2))
    printf("Yes \n");
  else
    printf("No \n");
  return 0;
}
