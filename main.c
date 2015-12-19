#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	ElementType Element;
	Position Next;
};

Position Next(Position P,List L){
	P=P->Next;
	return P;
}

void print_list(List L,Position P){
     while(P!=NULL){
		 printf("%d",P->Element);
		 P=P->Next;
	 }
}


List Intersec(List L1,List L2){
	List result;
	Position P1,P2,resultP;
	P1=First(L1);
	P2=First(L2);
	MakeEmpty(result);
	resultP=First(result);
	while(P1!=NULL&&P2!=NULL){
        if(P1->Element<P2->Element)
			P1=Next(P1,L1);
		else if(P1->Element>P2->Element)
			P2=Next(P2,L2);
		else
		{
			Insert(P1->Element,result,resultP);
			resultP=Next(resultP,result);
			P1=Next(P1,L1);
			P2=Next(P2,L2);
		}
	}
	return result;
}


int  main(){

	List list=malloc(sizeof(struct Node));
    if(!IsEmpty(list))
		printf("not empty");
	Position P=list;
    //insert elements
	for(int i=0;i<10;i++){
		Insert(i,list,P);
		P=P->Next;
	}
	P=list->Next;
    //print elements
    print_list(list,P); 
	//delet elements
	Delete(4,list);
    
	List list1=malloc(sizeof(struct Node));
	P=list->Next;
    print_list(list,P);
    List new_list= Intersec(list1,list);
    Position new_P=new_list->Next;
    print_list(new_list,new_P);

	return 0;
}
