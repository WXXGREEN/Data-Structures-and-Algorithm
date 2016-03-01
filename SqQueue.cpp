//队列的顺序存储(循环队列)
//by zoe

/*由于顺序队列会存在假溢出情况，所以将其变为循环队列*/

#include <stdio.h>
#include <stdlib.h>

#define maxsize 100
typedef char Elemtype;

int m=sizeof(Elemtype);

typedef struct {
	Elemtype *base;
	int front; //队首指针
	int rear;  //队尾指针
}SqQueue,Q;

int InitQueue(SqQueue &Q){
	Q.base=(Elemtype *)malloc(maxsize*m);
	if(!Q.base) return -1;
	Q.front=Q.rear=0;
	return 0;
}

int EnQueue(SqQueue &Q,Elemtype x){
	//先判断队列是否已满
	if((Q.rear+1)%maxsize==Q.front) return -1;
	Q.base[Q.rear]=x;
	Q.rear=(Q.rear+1)%maxsize; //尾指针循环后移一个位置
	return 0;
}

int DeQueue(SqQueue &Q,Elemtype x){
	//队空条件
	if(Q.rear==Q.front) return -1;
	x=Q.base[Q.front];
	Q.front=(Q.front+1)%maxsize;
	return 0;
}

int QueueLength(SqQueue Q){
	return (Q.rear-Q.front+maxsize)%maxsize;
}

int PrintQueue(SqQueue Q){
	if(Q.rear==Q.front) return -1;
	while(Q.front!=Q.rear){
	  int x=Q.base[Q.front++];
	  printf("%d",x);
	}
	return 0;
}

int main(){
	SqQueue Q;
	InitQueue(Q);
	int x=0,y=0;
  for(int i=0;i<7;i++){
		EnQueue(Q,i);
	}
	PrintQueue(Q);
	printf("\n");
	x=QueueLength(Q);
	printf("the length of the queue is: %d\n",x);
	DeQueue(Q,y);
	PrintQueue(Q);
	printf("\n");
	return 0;
}
