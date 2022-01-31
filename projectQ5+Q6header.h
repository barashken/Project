#ifndef H56_H
#define H56_H

#include "projectHeader.h"
#include "projectQ1+Q2header.h"
#include "projectQ3+Q4header.h"


/*5*/
void saveListToBinFile(char* file_name, chessPosList* pos_list);
BYTE intToByte(int num);
/*6*/
int checkAndDisplayPathFromFile(char* file_name);
int binToInt(BYTE mask);
void insertNodeToEndList(chessPosList* list, chessPos possition);
int isBitISet(BYTE ch, int i);
bool checkIfListCoverAllBoard(chessPosList* list);
bool checkValidRoute(chessPosList* list);


#endif