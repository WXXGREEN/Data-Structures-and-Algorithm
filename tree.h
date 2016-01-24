#pragma once

#ifndef _Tree_H
#define ElementType int
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FinMin(SearchTree T);
Position FinMax(SearchTree T);
SearchTree Delet(ElementType X, SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
ElementType Retrive(Position P);

#endif

struct TreeNode {
	ElementType element;
	SearchTree left;
	SearchTree right;
};