//二叉查找树的链式表示及算法实现
//by zoe

#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct node* position;
typedef int DataType;

struct node{
  DataType data;
  position lchild;
  position rchild;
  position parent;
}

typedef struct node* BiTree;

void Print_Tree(BiTree);
void Insert_node(BiTree,DataType);
position Find_Min(BiTree);
position Find_Max(Bitree);
position Find_Value(BiTree,DataType);
DataType Delete_node(position);
static int is_leaf(position);
static int is_root(position);
static DataType delete_leaf(position);
static void Insert_node_to_unempty_tree(BiTree,position);

int main(){
  BiTree tree;
  DataType data;
  position p;
  //tree=NULL;

  tree=Insert(tree,28);
  tree=Insert(tree,13);
  tree=Insert(tree,2);
  tree=Insert(tree,10);
  tree=Insert(tree,14)
  tree=Insert(tree,5);
  tree=Insert(tree,20);
  Print_Tree(tree);
  printf("\n");
  p=Find_Value(tree,14);
  if(p!=NULL){
    Delet_Data(p);
    printf("after delete: ");
    Print_Tree(tree);
  }
  return 0;
}

void Print_Tree(BiTree tree){
  if(tree!=NULL){
    Print_Tree(tree->lchild);
    printf("%d\n",tree->data);
    Print_Tree(tree->rchild);
  }
  else return;
}

void Insert_node(BiTree tree,DataType x){
  position np;
  np=(position)malloc(sizeof(struct node));//先挖坑，再插入
  np->data=x;
  np->parent=NULL;
  np->lchild=NULL;
  np->rchild=NULL;
  if(tree==NULL){
     tree=np;
  }
  else{
    Insert_node_to_unempty_tree(tree,np);
  }
}

position Find_Min(BiTree tree){
  position np;
  np=tree;
  if(np==NULL) return np;
  while (np->lchild!=NULL) {
    np=np->lchild;
  }
  return np;
}

position Find_Max(Bitree tree){
  position np;
  np=tree;
  if(np==NULL)return np;
  while(np->rchild!=NULL){
    np=np->rchild;
  }
  return np;
}

position Find_Value(BiTree tree,DataType x){
  position np;
  tree=np;
  if(np==NULL) return np;
  if(np->data==x) {return np;}
  /**
  /*迭代非递归
  while(np->lchild!=NULL||np->rchild!=NULL){
    if(x<np->data)
       Find_Value(np->lchild,x);
    else
       Find_Value(np->rchild,x);
  }
  */
  else if(x<np->data){
    return Find_Value(np->lchild,x);
  }
  else{
    return Find_Value(np->rchild,x);
  }
}

DataType Delete_node(position np){
  position replace;
  DtaType temp;
  //如果该结点为叶子结点，则直接删除
  if(is_leaf(np)){
    return delete_leaf(np);
  }
  //如果该结点有儿子结点，则要进行替换
  else{
    repalce=(np->lchild!=NULL)? Find_Max(np->lchild):Find_Min(np->rchild);
    temp=np->data;
    np->data=Delete_node(replace);
    return temp;
  }
}

static int is_leaf(position np){
  return (np->lchild==NULL&&np->rchild==NULL);
}

static int is_root(position np){
  return (np->parent==NULL);
}

static DataType delete_leaf(position np){
  DataType elem;
  positon parent;
  elem=np->data;
  parent=np->parent;
  if(!is_root(np)){
    if(parent->lchild==np){
      parent->lchild==NULL;
    }
    else{
      parent->rchild==NULL;
    }
  }
  free(np);
  return elem;
}

static void Insert_node_to_nonempty_tree(BiTree tree,position np){
  if(np->data<tree->data){
    if(tree->lchild==NULL){
      tree->lchild=np;
      np->parent=tree;
    }
    else{
      Insert_node_to_nonempty_tree(tree->lchild,np);
    }
  }
  else if(np->data>tree->data){
    if(tree-<rchild==NULL){
      tree->rchild=np;
      np->parent=tree;
    }
    else{
      Insert_node_to_nonempty_tree(tree->rchild,np);
    }
  }
}
