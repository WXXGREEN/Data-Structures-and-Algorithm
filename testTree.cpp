#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	SearchTree T;
	Position P;
	int i, j = 0;
	T = MakeEmpty(NULL);
	for (i = 0; i < 50; i++, j = (j + 7) % 50)
		T = Insert(j, T);
	printf("Min is %d,Max is %d", Retrive(FinMin(T)), Retrive(FinMax(T)));
	return 0;
}