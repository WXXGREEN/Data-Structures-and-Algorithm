#include <cstdio>
#include <cstdlib>
#include <iostream>

typedef int Type;
typedef struct PolyNode *PolyNomial;
struct PolyNode {
  Type coef;
  Type expo;
  PolyNomial link;
};

//多项式读入函数
void attach(Type e, Type c, PolyNomial *PtrRear) {
  /*注意这里PtrRear实际上是指针的指针，为什么这么做呢？由于在本函数中要改变d当前结果表达式尾指针的值，
  所以函数传递进来的是结点指针的地址，*PtrRear指向尾项*/
  /*因为c语言中函数参数传递要改变参数值应采用传址方式*/
  PolyNomial P;
  P = (PolyNomial)malloc(sizeof(struct PolyNode));
  P->coef = c;
  P->expo = e;
  P->link = NULL;
  (*PtrRear)->link = P;
  (*PtrRear) = P;
}

PolyNomial ReadPloy() {
  int N, c, e;
  PolyNomial P, Rear, t;
  //生成一个头节点来使Rear指向它
  P = (PolyNomial)malloc(sizeof(struct PolyNode));
  P->link = NULL;
  Rear = P;
  scanf("%d", &N);
  while (N--) {
    scanf("%d%d", &c, &e);
    attach(e, c, &Rear);
  }
  //删除临时生成的头节点
  t = P;
  P = P->link;
  free(t);
  return P;
}

PolyNomial Add(PolyNomial P1, PolyNomial P2) {
  PolyNomial t1, t2, P, Rear;
  t1 = P1;
  t2 = P2;
  P = (PolyNomial)malloc(sizeof(struct PolyNode));
  P->link = NULL;
  Rear = P;
  while (t1 && t2) {
    if (t1->expo == t2->expo) {
      attach(t1->expo, t1->coef + P2->coef, &Rear);
      t1 = P1->link;
      t2 = P2->link;
    } else if (t1->expo > t2->expo) {
      attach(t1->expo, t1->coef, &Rear);
      t1 = t1->link;
    } else {
      attach(t2->expo, t2->coef, &Rear);
      t2 = t2->link;
    }
  }
  while (t1) {
    attach(t1->expo, t1->coef, &Rear);
    t1 = t1->link;
  }
  while (t2) {
    attach(t2->expo, t2->coef, &Rear);
    t2 = t2->link;
  }
  return P;
}

PolyNomial Multi(PolyNomial P1, PolyNomial P2) {
  PolyNomial t1, t2, P, Rear, t;
  int c, e;
  P = (PolyNomial)malloc(sizeof(struct PolyNode));
  P->link = NULL;
  Rear = P; // Rear指向头节点
  t1 = P1;
  t2 = P2;
  //边界条件：如果两个多项式中有一个为空，则相乘结果为0
  if (!t1 || !t2)
    return NULL;
  //先让p1的第一项与p2的所有项相乘，得到初始的P
  while (t2) {
    attach(t1->expo + t2->expo, t1->coef * t2->coef, &Rear);
    t2 = t2->link;
  }
  t1 = t1->link;
  //让p1的第一项后的所有项分别与p2相乘
  while (t1) {
    t2 = P2; //注意没循环一遍要使指针回到表首节点
    Rear = P;
    while (t2) {
      c = t1->coef * t2->coef;
      e = t1->expo + t2->expo;
      //插入初始链表的适当位置,指数大于则继续寻找，相等则合并，小于则插入
      while (Rear->link && Rear->link->expo > e) {
        Rear = Rear->link;
        if (Rear->link && Rear->link->expo == e) {
          if (Rear->link->coef + c)
            Rear->link->coef += c;
          else {
            t = Rear->link;
            Rear->link = t->link;
            free(t);
          }
        } else {
          //生成新节点插入之
          t = (PolyNomial)malloc(sizeof(struct PolyNode));
          t->link = NULL;
          t->coef = c;
          t->expo = e;
          t->link = Rear->link;
          Rear->link = t;
          Rear = Rear->link;
        }
      }
      t2 = t2->link;
    }
    t1 = t1->link;
  }
  t2 = P;
  P = P->link;
  free(t2);
  return P;
}

void PrintPoly(PolyNomial P) {
  int flag = 0;
  if (!P) {
    printf("0 0");
    return;
  }
  while (P) {
    if (!flag)
      flag = 1;
    else
      printf(" ");
    printf("%d%d", P->coef, P->expo);
    P = P->link;
  }
}

int main() {
  PolyNomial P1, P2, Psum, Pmulti;
  P1 = ReadPloy();
  P2 = ReadPloy();
  Psum = Add(P1, P2);
  Pmulti = Multi(P1, P2);
  PrintPoly(Pmulti);
  printf("\n");
  PrintPoly(Psum);
  return 0;
}
