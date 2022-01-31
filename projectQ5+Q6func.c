#include "projectHeader.h"
#include "projectQ1+Q2header.h"
#include "projectQ3+Q4header.h"
#include "projectQ5+Q6header.h"


/*5*/

/*this function fwrites the possitions from chessPosList to bin file*/
void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	FILE* fp;
	chessPosCell* cur = pos_list->head;
	unsigned short int count = 0;
	BYTE mask1, mask2, mask3, mask4, byte1, byte2, byte3, temp1, temp2;

	fp = fopen(file_name, "wb");
	checkMemoryAllocation(fp);

	fwrite(&count, sizeof(short int), 1, fp);/*save space for the number of possitions written at the end*/

	while (cur != NULL)
	{
		mask1 = intToByte(cur->position[0]-'A');
		mask2 = intToByte(cur->position[1]-'1');
		cur = cur->next;
		count++;
		if (cur == NULL)
		{
			mask3 = 0x0;
			byte1 = (mask1 << 5) | (mask2 << 2) | (mask3);
			fwrite(&byte1, sizeof(BYTE), 1, fp);
		}
		else
		{
			mask3 = intToByte(cur->position[0] - 'A');
			temp1 = mask2;
			temp1 = temp1 << 5;
			temp1 = temp1 >> 3;

			temp2 = mask3;
			temp2 = temp2 << 5;
			temp2 = temp2 >> 6;

			byte1 = (mask1 << 5) | temp1 | temp2;
			fwrite(&byte1, sizeof(BYTE), 1, fp);

			mask1 = intToByte(cur->position[1] - '1');
			cur = cur->next;
			count++;
			if (cur == NULL)
			{
				mask2 = 0x0;
				byte2 = (mask3 << 7) | (mask1 << 4) | mask2;
				fwrite(&byte2, sizeof(BYTE), 1, fp);
			}
			else
			{
				temp1 = mask1;
				temp1 = temp1 << 4;
				mask2 = intToByte(cur->position[0] - 'A');
				mask4 = intToByte(cur->position[1] - '1');

				byte2 = (mask3 << 7) | temp1 | (mask2 << 1) | (mask4 >> 2);
				fwrite(&byte2, sizeof(BYTE), 1, fp);

				cur = cur->next;
				count++;
				if (cur == NULL)
				{
					mask1 = 0x0;
					byte3 = (mask4 << 6) | mask1;
					fwrite(&byte3, sizeof(BYTE), 1, fp);
				}
				else
				{
					mask1 = intToByte((cur->position[0]) - 'A');
					mask2 = intToByte(cur->position[1] - '1');
					cur = cur->next;
					count++;

					byte3 = (mask4 << 6) | mask1<<3 | (mask2);
					fwrite(&byte3, sizeof(BYTE), 1, fp);
				}
			}
		}
	}
	rewind(fp);
	fwrite(&count, sizeof(short int), 1, fp);

	freeList(pos_list);
	fclose(fp);
}

/*this function returns the byte of the number*/
BYTE intToByte(int num)
{
	BYTE newByte;

	switch (num)
	{
	case 0:
		newByte = 0x0;
		break;
	case 1:
		newByte = 0x01;
		break;
	case 2:
		newByte = 0x02;
		break;
	case 3:
		newByte = 0x03;
		break;
	case 4:
		newByte = 0x04;
		break;
	case 5:
		newByte = 0x05;
		break;
	case 6:
		newByte = 0x06;
		break;
	case 7:
		newByte = 0x07;
		break;
	}
	return newByte;
}


/*6*/

/*this function reads list from file and check is it's route is valid, delete the double cells and checks if the route is cover all the board*/
int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* fp;
	short int sizeOfList, count = 0;
	chessPos possition;
	BYTE byte1, byte2, byte3;
	BYTE mask1, temp;
	BYTE letInBin, numInBin;
	bool endOfList = false;
	char let, num;
	int res;

	fp = fopen(file_name, "rb");
	if (fp == NULL)
	{
		printf("File %s does not exist\n", file_name);
		return -1;
	}
	chessPosList* list;
	list = makeEmptyList();
	fread(&sizeOfList, sizeof(short int), 1, fp);

	while (!endOfList)
	{
		fread(&byte1, sizeof(BYTE), 1, fp);
		mask1 = 0xFF;	/*11111111*/

		letInBin = mask1&(byte1>>5);
		let = 'A' + binToInt(letInBin);

		temp = byte1;
		temp = temp << 3;
		temp = temp >> 5;
		numInBin = mask1 & temp ;
		num = '1' + binToInt(numInBin);

		possition[0] = let;
		possition[1] = num;
		insertNodeToEndList(list, possition);
		count++;
		if (count == sizeOfList)
			endOfList = true;
		else
		{
			fread(&byte2, sizeof(BYTE), 1, fp);
			temp = byte1;
			temp = temp << 6;
			temp = temp >> 5;

			letInBin = temp | (byte2>>7) ;
			let = 'A' + binToInt(letInBin);

			temp = byte2;
			temp = temp << 1;
			temp = temp >> 5;

			numInBin = temp & mask1;
			num = '1' + binToInt(numInBin);

			possition[0] = let;
			possition[1] = num;
			insertNodeToEndList(list, possition);
			count++;
			if (count == sizeOfList)
				endOfList = true;
			else
			{
				temp = byte2;
				temp = temp << 4;
				temp = temp >> 5;
				letInBin = mask1 & temp;
				let = 'A' + binToInt(letInBin);

				fread(&byte3, sizeof(BYTE), 1, fp);

				temp = byte2;
				temp = temp << 7;
				temp = temp >> 5;
				numInBin = temp | (byte3>>6);
				num = '1' + binToInt(numInBin);

				possition[0] = let;
				possition[1] = num;
				insertNodeToEndList(list, possition);
				count++;
				if (count == sizeOfList)
					endOfList = true;
				else
				{
					temp = byte3;
					temp = temp << 2;
					temp = temp >> 5;

					letInBin = mask1 & temp;
					let = 'A' + binToInt(letInBin);

					temp = byte3;
					temp = temp << 5;
					temp = temp >> 5;
					numInBin = temp & mask1;
					num = '1' + binToInt(numInBin);

					possition[0] = let;
					possition[1] = num;
					insertNodeToEndList(list, possition);
					count++;
					if (count == sizeOfList)
						endOfList = true;
				}

			}
		}
	}

	if (!checkValidRoute(list))
	{
		printf("the route is not valid\n");
		res = 1;
	}
	else
	{
		display(list);
		if (checkIfListCoverAllBoard(list))
		{
			printf("the list cover all the board\n");
			res = 2;
		}
		else
		{
			printf("the list do not cover all the board\n");
			res = 3;
		}
	}

	freeList(list);
	return res;
}

/*this function returns if the route is valid*/
bool checkValidRoute(chessPosList* list)
{
	chessPosArray*** board;
	chessPosCell* cur = list->head;
	int i, size;

	bool isValid = true, isfound = false;
	board = validKnightMoves();

	while (cur->next != NULL && isValid)
	{
		int row = cur->position[0] - 'A';
		int cul = cur->position[1] - '1';
		size = board[row][cul]->size;
		for (i = 0; i < size && !isfound; i++)
		{
			if (board[row][cul]->positions[i][0] == cur->next->position[0]
				&& board[row][cul]->positions[i][1] == cur->next->position[1])
				isfound = true;
		}
		if (!isfound)
			isValid = false;
		cur = cur->next;
	}

	freeChessPosArray(board);
	return isValid;
}

/*this function check If the List Cover All Board*/
bool checkIfListCoverAllBoard(chessPosList* list)
{
	chessPosCell* cur = list->head;
	int count = 0;

	while (cur != NULL)
	{
		count++;
		cur = cur->next;
	}
	return (count == ROWSIZE * CULSIZE);
}

/*this function convert bin to int*/
int binToInt(BYTE mask)
{
	int num, i, res=0;
	for (i = 0; i < 8; i++)
		res = res + ( isBitISet(mask, i) * (int)(pow(2, i)));

	return res;
}

/*this function returns the int num of the bin mask*/
int isBitISet(BYTE ch, int i)
{
	BYTE temp, mask = 0xFF;
	temp = ch;
	temp = temp << (7 - i);
	temp = temp >> 7;
	return mask & temp;
}

/*this function insert new chessPosCell to end of chessPosList*/
void insertNodeToEndList(chessPosList* list, chessPos possition)
{
	chessPosCell* newNode;
	newNode = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(newNode);

	newNode->position[0] = possition[0];
	newNode->position[1] = possition[1];
	newNode->next = NULL;

	if (list->head == NULL)
	{
		list->head = newNode;
		list->tail = newNode;
	}

	else
	{
		list->tail->next = newNode;
		list->tail = list->tail->next;
	}
}
