nclude <stdio.h>
#include <stdlib.h>

typedef int Elemtype;
typedef struct node{
	 Elemtype elem;
	  struct node *next;
}*top;
int m=sizeof(struct node);

struct node *Push(struct node *top,Elemtype x){
	 struct node *p;
	 p=(struct node *)malloc(m);
	 p->next=top;
	 top=p;
	 p->elem=x;
     return top;
}

struct node *Pop(struct node *top,Elemtype &x){
	 if(top==NULL) return 0;
	 struct node *p;
	 p=top;
	 x=p->elem;
	 top=top->next;
	 delete p;
	 return top;
}

Elemtype GetTop(struct node *top){
	 if(top==NULL) return -1;
	 int x=top->elem;
	 return x;
}

int main(){
	 struct node *top;
	 int x=0,y=0;
	 top=Push(top,2);
	 top=Push(top,34);
	 top=Pop(top,x);
	 printf("%d\n",x);
	 y=GetTop(top);
	 printf("%d\n",y);
	 return 0;
}

