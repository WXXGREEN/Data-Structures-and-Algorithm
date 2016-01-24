#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

SearchTree MakeEmpty(SearchTree T) {
	if (T != NULL);
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right); 

	}
	return T;
}

Position Find(ElementType X, SearchTree T) {
	if (T == NULL)
		return NULL;
	if (X < T->element)
		Find(X, T->left);
	else if (X > T->element)
		Find(X, T->right);
	else
		return T;
}

Position FinMin( SearchTree T) {
	if (T == NULL)
		return NULL;
	else if (T->left == NULL)
		return T;
	else
		FinMin(T->left);
}

Position FinMax(SearchTree T) {
	if (T == NULL)
		return NULL;
	else if (T->right == NULL)
		return T;
	else
		FinMax(T->right);
}

SearchTree Insert(ElementType X, SearchTree T) {
	if (T == NULL) {
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if (T == NULL)
			printf("out of memory!");
		else {
			T->element = X;
			T->left = NULL;
			T->right = NULL;
		}
	}
	//�ݹ����
	else if (X < T->element)
		T ->left= Insert(X, T->left);
	else if (X > T->element)
		T ->right= Insert(X, T->right);
	return T;
}

SearchTree Delet(ElementType X, SearchTree T) {
	Position TempCell;
	if (T == NULL)
		printf("out of memory!");
	else if (X < T->element)
		T->left = Delet(X, T->left);
	else if (X > T->element)
		T->right = Delet(X, T->right);
	//�ҵ���Ԫ��X�������������������
	else if (T->left&&T->right) {
		TempCell = FinMin(T->right);
		T->element = TempCell->element;
		T->right = Delet(T->element, T->right);
	}
	//���ֻ��һ�����ӻ�û�ж���
	else {
		TempCell = T;
		if (T->left == NULL)
			T = T->right;
		else if (T->right == NULL)
			T = T->left;

		free(TempCell);
	}
	return T;
}

ElementType Retrive(Position P) {
	return P->element;
		
}














