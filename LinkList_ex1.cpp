#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct Lnode {
  int elem;
  struct Lnode *next;
}Lnode,*Linklist;

int m=sizeof(Lnode); //结构类型定义好之后，每个变量的长度就固定了

void CreateList(Linklist &L,int n){
  L=(Linklist )malloc(m);
  L->next=NULL;     //建立一个带头结点的单链表
  for(int i=0;i<n;i++){
    Lnode *p=(Linklist)malloc(m);
    cin>>p->elem;
    p->next=L->next;
    L->next=p;
  }
}

void PrintList(Linklist L){
  Linklist p=L->next;
  while(p!=NULL){
    printf("%d ",p->elem);
    p=p->next;
  }
}

//归并两个递减的表，新表为递增
void MergeList(Linklist &La,Linklist &Lb){
  Lnode *pa,*pb,*p;
  pa=La->next;
  pb=Lb->next;
  La->next=NULL; //断开a表的头结点，以使c表的元素插入a表的表头
  //delete Lb;
  while(pa!=NULL&&pb!=NULL){
    if(pa->elem<=pb->elem){p=pa;pa=pa->next;}
    else{p=pb;pb=pb->next;}
    p->next=La->next;
    La->next=pa;
  }
  if(pb!=NULL) pa=pb;
  while(pa!=NULL){p=pa;pa=pa->next;p->next=La->next;La->next=p;}

}

//统计表中具有某值的结点数
int Count(Linklist &L,int x){
  int n=0;
  Lnode *p=L->next;
  while(p!=NULL){
    if(p->elem==x){
       n++;
       p=p->next;}

  }
  return n;
}

//就地反转链表算法
void ReverseList(Linklist &L){
  Lnode *pr,*p;   //设置遍历指针
  p=L->next;
  L->next=NULL;   //断开头结点
  while(p!=NULL){
    pr=p;
    p=p->next;
    pr->next=L->next;  //将新元素插入到链表前端，先插的被推至后方，这样就实现了链表反转
    L->next=pr;
  }
}

int main(){
  Linklist LA,LB;
  int n=5;
  int x,count;
  CreateList(LA,n);
  CreateList(LB,n);
  PrintList(LA);
  cout<<endl;
  PrintList(LB);
  cout<<endl;
  //cout<<"what is the number to count?"<<endl;
  //cin>>x;
  //count=Count(LA,x);
  //cout<<"the number is: "<<count<<endl;
  MergeList(LA,LB);
  PrintList(LA);
  ReverseList(LA);
  PrintList(LA);
  return 0;
}
