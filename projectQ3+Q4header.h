#ifndef H34_H
#define H34_H

#include "projectHeader.h"
#include "projectQ1+Q2header.h"


/*3*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
bool** makeBoolArr(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathsHelper(chessPos curPosition, chessPosArray*** math, bool** route);
void insertTreeNodeToStartList(treeNode* node, treeNodeListCell** list);
/*4*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosList* findKnightPathCoveringAllBoardHelper(treeNode* root, int* hight);
void insertChessPosToStartchessPosList(chessPos position, chessPosList* ListPath);
void freeList(chessPosList* ListPath);



#endif