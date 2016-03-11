/*最优树（赫夫曼树）的实现
by zoe
哈夫曼树中没有度为1的结点。
若有n个叶子结点,则其共有2n-1个结点。
 Huffman编码时是从叶子走到根;而译码时又要从根走到叶子,因此每个结点需要增开双亲指针分量。
实现时,要用到顺序和链式两种存储结构。
*/

#include <cstdio>
#include <stdlib>
typedef struct{
  unsigned int weight;//权重
  unsigned int lchild,rchild,parent;
}HTNode,*HuffmanTree;//动态分配数组存储赫夫曼树

typedef char* *HuffmanCode;//动态分配数组存储赫夫曼编码表

//w为权重，n为字符个数。构造赫夫曼树的算法如下：
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
  if(n<=1) return ;
  int m=2*n-1;
  HT=(HuffmanTree)malloc(n*sizeof(HTNode));
  HuffmanTree p;
  int i;
  for(p=HT,i=1;i<=n;++i,++p,++w) *p={*w,0,0,0};
  for(;i<m;i++) *p={0,0,0,0};
  //建赫夫曼树
  for(int i=n+1;i<=m;i++){
    //在HT选择paren为0且权重最小的两个结点，其序号分别为s1,s2
    Select(HT,i-1,s1,s2);
    HT[s1].parent=i; HT[s2].parent=i;
    HT[i].lchild=s1; HT[i].rchild=s2;
    HT[i].weight=HT[s1].weight+HT[s2].weight;
  }

  //从叶结点到根逆向求每个字符的赫夫曼编码
  HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
  char *cd;
  cd=(char *)malloc(n*sizeof(char));
  cd[n-1]="\0";
  //逐个字符求赫夫曼编码
  for(int i=1;i<=n;i++){
    int start=n-1;
    unsigned int f;
    for(int c=i,f=HT[i].parent;f!=0;c=f;f=HT[f].parent){
      if(c==HT[f].lchild) cd[--start]="0";
      else cd[--start]="1";
    }
    HC[i]=(char *)malloc((n-start)*sizeof(char));
    strcpy(HC[i],&cd[start]);
  }
  free(cd);
}
