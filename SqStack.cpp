//栈的顺序存储及其算法实现
//by zoe

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

/*//顺序栈的静态存储
#define MaxSize 100
typedef char Elemtype;
typedef struct {
  Elemtype elem[MaxSize];
  int top;  //栈顶指针
}SeqStack;*/

//顺序栈的动态存储
#define initSize 100
#define increment 10
typedef char Elemtype;
typedef struct {
  Elemtype *base; //栈的基址指针
  Elemtype *top;
  int StackSize;
}SqStack;

int m=sizeof(Elemtype);

int InitStack(SqStack &S){
  S.base=(Elemtype *)malloc(initSize*m);
  if(!S.base) return -1;
  S.top=S.base;   //构造一个空栈
  S.StackSize=initSize;
}

int Push(SqStack &S,Elemtype x){
  //考虑栈满情况
  if(S.top-S.base>S.StackSize){
    S.base=(Elemtype *)realloc(S.base,(S.StackSize+increment)*m);
    if(!S.base) return -1;
    S.top=S.base+S.StackSize;//思考：为何不是原来的S.top了？
    S.StackSize+=increment;
  }
  *S.top++=x; //先插入元素，再使指针加一,栈顶指针始终指向栈顶元素的下一个位置
}

int Pop(SqStack &S,Elemtype x){
  //考虑栈空情况
  if(S.top==S.base) return -1;
  x=*--S.top;
}

int GetTop(SqStack S,Elemtype x){
  if(S.top==S.base) return -1;
  x=*(S.top-1);
}

void PrintStack(SqStack &S){
  if(S.top!=S.base){
    printf("&d ",*S.top);
    S.top--;
  }
}

int main(){
   SqStack S1,S2;
   Elemtype x;
   InitStack(S1);
   InitStack(S2);
   Push(S1,10);
   Push(S1,23);
   Push(S1,45);
   PrintStack(S1);
   return 0;
 }
