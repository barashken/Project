#ifndef H12_H
#define H12_H

#include "projectHeader.h"


/*1*/
chessPosArray*** validKnightMoves();
bool checkValidPos(int row, int cul);
chessPosArray* positionsKnightArr(int row, int cul);
/*2*/
void printBoard(int arr[][CULSIZE]);
void display(chessPosList* lst);
void deleteDoubleCells(chessPosList* lst);


#endif 
