#ifndef H_H
#define H_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define ROWSIZE 5
#define CULSIZE 5

typedef unsigned char BYTE;

typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;


typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions; 
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListcell* next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
}pathTree;

void freeChessPosArray(chessPosArray*** c);
void freePosArr(chessPosArray* c);
void freeArrBool(bool** arr);
void freeTree(treeNode* root);
chessPosList* makeEmptyList();
void checkMemoryAllocation(void* arr); 

#endif 
