/*各种排序算法的实现：
插入排序、交换排序、选择排序、归并排序、基数排宿
by zoe*/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAXSIZE 6
#define  LENGTH 6
typedef int DataType;
typedef int infoType;

using namespace std;

typedef struct {
  DataType key;
  infoType others;
}Node;

typedef struct{
  Node r[MAXSIZE+1];//这里加一是为了方便插入排序时数组序号的理解，第一个数的序号为1，i应从2开始
  int length;
}SqList;

void InsertSort(SqList &L);
void QuickSort(SqList &L,int low,int high);
int partiton(SqList &L,int low,int high);



int main(){
  SqList L;
  int i=1;
  int low,high;
  L.length=LENGTH;

  printf("请输入序列：\n" );
  for(i=1;i<L.length;i++){
    scanf("%d",&L.r[i].key );
  }
  low=1;
  high=L.length;

  InsertSort(L);
  //QuickSort(L,low,high);
  //sort(L.r,L.r+9);
  printf("排序后的序列为：\n " );
  for(i=1;i<L.length;i++){
    printf("%d ",L.r[i].key );
  }
  printf("\n" );
  return 0;
}

//基本插入排序
void InsertSort(SqList &L){
  int i,j;
  for( i=2;i<L.length;++i){

    if(L.r[i-1].key>L.r[i].key) {
      L.r[0]=L.r[i];
      L.r[i]=L.r[i-1];
    for(j=i-2;L.r[j].key>L.r[i].key;j--){
      L.r[j+1]=L.r[j];
    }
    L.r[j+1]=L.r[0];
  }
 }
}

//递归实现快速排序
void QuickSort(SqList &L,int low,int high){
  if(low<high){
    int pivotLoc=partiton(L,low,high);
    QuickSort(L,pivotLoc+1,high);//在中间点的右边排
    QuickSort(L,low,pivotLoc-1);//在中间点的左边排
  }
}

//确定中间位置，交换相应元素，使在它左边的都比它小，在它右边的都比它大
int partiton(SqList &L,int low,int high){
  L.r[0]=L.r[low];
  int pivotValue=L.r[low].key;
  while(low<high){
    while(low<high&&L.r[high].key>pivotValue) high--;
    //如果遇到比pivotValue小的元素，则交换到矮子的那边
    L.r[low]=L.r[high];
    while(low<high&&L.r[low].key<pivotValue) low++;
    //如果遇到比pivotValue大的元素，则交换到高的那边
    L.r[high]=L.r[low];
  }
  //最后找到了位置
  L.r[low]=L.r[0];
  return low;
}

//堆排序
