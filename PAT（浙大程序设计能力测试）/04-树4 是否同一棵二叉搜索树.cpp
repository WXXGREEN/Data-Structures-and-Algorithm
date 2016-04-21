/*判断是否是同一棵二叉搜索树：对于各种输入不同的序列，判断它们是否构成一样的二叉搜索树*/
#include <cstdio>
#include <cstdlib>
#include <stack>
using namespace std;

//二叉树的表示
typedef int DataType;
typedef struct TreeNode *Tree;
typedef struct TreeNode {
  DataType v;
  Tree left;
  Tree right;
  bool flag; //用于标记是否在之前经过
} treeNode;

//二叉树的建立
Tree NewNode(int V) {
  Tree T = (Tree)malloc(sizeof(struct TreeNode));

  T->flag = 0;
  T->left = NULL;
  T->right = NULL;
  T->v = V;
  return T;
}

Tree Insert(Tree T, int V) {
  // printf("V:%d  ", V);
  if (!T)
    T = NewNode(V);
  else {
    if (V > T->v)
      T->right = Insert(T->right, V);
    else
      T->left = Insert(T->left, V);
  }
  return T;
}

Tree BuiltTree(int N) {
  Tree T;
  int V, i;
  scanf("%d", &V);
  //先建立一个头节点
  T = NewNode(V);
  //特别注意这里i是从1开始的，因为头节点先建立了
  for (i = 1; i < N; i++) {
    scanf("%d", &V);
    T = Insert(T, V);
  }
  // printf("built tree !\n");
  return T;
}

/*void PreoderPrintTree(Tree T) {
  int temp;
  stack<int> S;

  // InitStack(S);
  while (T || !S.empty()) {
    while (T) {

      S.push(T->v);
      T = T->left;
    }
    if (!S.empty()) {

      temp = S.top();
      S.pop();

      printf("%d ", temp);
      printf("using stack to print\n");
      T = T->right;
    }
  }
}*/

/*void PreOrderPrintTree(Tree T) {
  if (!T)
    return;
  printf("%d", T->v);
  PreOrderPrintTree(T->left);
  PreOrderPrintTree(T->right);
}*/

//判断输入系列与二叉树是否相等
//检查每次搜索中是否出现前面未出现的点
int check(Tree T, int V) {
  // printf("in \n");
  //如果当前点已出现过，则递归找左右子树
  if (T->flag) {
    if (V > T->v) {
      // printf("the right one\n");
      return check(T->right, V);
    } else if (V < T->v)
      return check(T->left, V);
    else
      return 0;
  }

  //如果当前点之前没有出现过，且与序列中的当前点相等，则将flag标志置为1，表示经过该点
  else {
    // printf("set right\n");
    if (T->v == V) {
      T->flag = 1;
      return 1;
    } else
      return 0;
  }
}

int Judge(Tree T, int N) {
  int V, i, flag = 0; //该flag表示到目前为止，flag＝0则一致，为1则不一致
  scanf("%d", &V);
  if (T->v != V) {
    // printf("the 1st node not equal\n");
    flag = 1;
  } else {
    // printf("1st's flag set to 1\n");
    T->flag = 1;
  }

  for (i = 1; i < N;
       i++) { //特别注意这里i是从1开始的，因为头节点之前已经比较过了
    scanf("%d", &V);
    if ((!flag) && (!check(T, V))) {
      // printf("not the same\n");
      flag = 1;
    } //如果头节点一致而后面有没有出现过的点出现
  }
  if (flag)
    return 0;
  else
    return 1;
}

void ResetTree(Tree T) {
  if (T->left)
    ResetTree(T->left);
  if (T->right)
    ResetTree(T->right);
  T->flag = 0;
}

void FreeTree(Tree T) {
  if (T->left)
    FreeTree(T->left);
  if (T->right)
    FreeTree(T->right);
  free(T);
}

int main() {
  Tree T;
  int N, L;
  scanf("%d", &N);
  while (N) {
    scanf("%d", &L);
    T = BuiltTree(N);
    // PreOrderPrintTree(T);
    for (int i = 0; i < L; i++) {
      if (Judge(T, N))
        printf("Yes\n");
      else
        printf("No\n");
      ResetTree(T); //清除flag标志
    }
    FreeTree(T);
    scanf("%d", &N);
  }
  return 0;
}
