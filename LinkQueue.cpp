//队列的链式存储
//by zoe

#include <cstdio>
#include <cstdlib>

typedef int Elemtype;
typedef struct Qnode{
  Elemtype elem;
  struct Qnode *next;
}Qnode,*ptrQnode;

typedef struct {
  Qnode *front;
  Qnode *rear;
}LinkQueue;

int m=sizeof(Qnode);

int EnQueue(LinkQueue &Q,Elemtype x){
  ptrQnode p;
  p=(ptrQnode)malloc(m);//生成新结点
  if(!p) return -1;
  p->elem=x;
  Q.rear->next=p;//在队尾插入新结点
  Q.rear=p;
  p->next=NULL; //这句特别容易忘记
  return 0;
}

int InitQueue(LinkQueue &Q){
  Q.front=Q.rear=(ptrQnode)malloc(m);//指向队头结点
  if(!Q.front) return -1;
  Q.front->next=NULL;
  return 0;
}

//出队时注意考虑只有一个元素的情况
int DeQueue(LinkQueue &Q,Elemtype &x){
  if(Q.front==Q.rear) return -1;//队列为空时
  ptrQnode p=Q.front->next; //设置指针指向队首结点
  x=p->elem;
  Q.front->next=p->next;
  if(Q.rear==p){   //若队列只有一个元素
    Q.rear=Q.front;
  }
  free(p);
  return 0;
}

int main(){
  LinkQueue Q;
  ptrQnode p;
  int x=0;
  InitQueue(Q);
  p=Q.front->next;
  EnQueue(Q,13);
  EnQueue(Q,45);
  EnQueue(Q,23);
  while(p!=NULL){
    printf("%d\n",p->elem);
    p=p->next;
  }
  printf("\n");
  DeQueue(Q,x);
  printf("%d\n",x);
  return 0;
}
