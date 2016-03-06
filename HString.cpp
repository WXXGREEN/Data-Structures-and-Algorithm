//串的动态堆分配存储
//by zoe

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define MAXSIZE 100
using namespace std;

typedef struct {
	char *ch;
	int length;
	int size;
}HString;

void InitString(HString &S){
	S.ch=new char[MAXSIZE];
	if(S.ch==NULL) {cerr<<"error!\n";exit(1);}
	S.ch[0]='\0';
	S.length=0;
	S.size=MAXSIZE;
}

int StrLength(HString S){
	return S.length;
}

//字符串复制
void StrAssign(HString &S,HString T){
  if(S.ch) delete S.ch;
	if(!T.ch) {exit(1);}
	else{
		if(!(S.ch=(char*)malloc(StrLength(T)*sizeof(char)))) {exit(1);}
		for(int i=1;i<=StrLength(T);i++){
			S.ch[i]=T.ch[i];
		}
		S.length=T.length;
		S.size=T.size;
	}
}

//若s>t,则返回值大于零；s=t，返回值等于0；s<t，返回小于零
int StrCompare(HString S,HString T){
	for(int i=0;i<S.length&&i<T.length;i++){
		if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
	}
	return S.length-T.length;
}

//将s2连接在s1后面
void Concat(HString &S1,HString &S2){
  int i=0,j;
	if((S1.length+S2.length)>MAXSIZE){
		char *dest=new char[S1.length+S2.length+1];
		if(dest==NULL) {cerr<<"error!\n";exit(1);}
		char *temp=dest;
		for(int i=0;i<S1.length;i++) dest[i]=S1.ch[i];
		delete [] S1.ch;
		S1.ch=temp;
		S1.size=S1.length+S2.length;
	}
	for(int j=0;j<S2.length;j++,i++) S1.ch[i]=S2.ch[j];
	S1.ch[i]='\0';
	S1.length=S1.length+S2.length;
}

HString SubString(HString S,int pos,int len ){
	HString sub;
	sub.ch=(char*)malloc(len*sizeof(char));
	if(!sub.ch) {cerr<<"error!\n";exit(1);}
	if(pos>=S.length||pos<0||len<0||len>S.length){
		sub.ch[0]='\0';sub.length=0;
	}
	else{
		if(pos+len-1>S.length) len=S.length-pos;
		for(int i=0,j=pos;i<len;i++,j++) sub.ch[i]=S.ch[j];
		sub.ch[len]='\0';
		sub.length=len;
	}

	return sub;
}

//在串s中删除与所有与串t相同的子串，并返回删除的次数
int Delete_SubString(HString &S,HString T){
	HString sub;
	HString lsub;
	InitString(sub);
	int m=StrLength(S);
	int n=StrLength(T);
	int i=1,count=0;
	while(i<=m){
		StrAssign(sub,SubString(S,i,n));
		if(StrCompare(sub,T)==0){//匹配相等
			InitString(sub);
			InitString(lsub);
			Concat(sub,lsub=SubString(S,1,i-1));
			Concat(sub,lsub=SubString(S,i+n,m-i-n+1));
			StrAssign(S,sub);
			n=StrLength(S); //要注意，操作完一次后s的值改变了
			count++;
		}
		else {
			i++;
		}
	}
	return count;
}

void PrintString(HString S){
	for(int i=0;i<S.length;i++){
		printf("%c ",S.ch[i]);
	}
}

int main(){
	HString S,T;
	InitString(S);
	InitString(T);
	char s1[]={"abcdefgabcimcseeokabcsf"};
	char s2[]={"bc"};
	for(int i=0;i<S.size;i++){
		S.ch[i]=s1[i];
		S.length=strlen(s1);
	}
	for(int i=0;i<T.size;i++){
		T.ch[i]=s2[i];
		T.length=strlen(s2);
	}
	int n=Delete_SubString(S,T);
	PrintString(S);
	printf("\n");
	PrintString(T);
	printf("\n");
	printf("%d\n",n);
	return 0;
}
