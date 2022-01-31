#include "projectHeader.h"
#include "projectQ1+Q2header.h"


/*1*/

/*this function returns the array of the positions of each cell in the board*/
chessPosArray*** validKnightMoves()
{
	int row, cul;

	chessPosArray*** pKnightArr;
	pKnightArr = (chessPosArray***)malloc(ROWSIZE * sizeof(chessPosArray**));
	checkMemoryAllocation(pKnightArr);
	for (row = 0; row < ROWSIZE; row++)
	{
		pKnightArr[row] = (chessPosArray**)malloc(CULSIZE * sizeof(chessPosArray*));
		checkMemoryAllocation(pKnightArr);
		for (cul = 0; cul < CULSIZE; cul++)
			pKnightArr[row][cul] = positionsKnightArr(row, cul);
	}
	return pKnightArr;
}

/*this function check if the position is valid.*/
bool checkValidPos(int row, int cul)
{
	if ((row < 0 || cul < 0) || (row >= ROWSIZE || cul >= CULSIZE))
		return false;
	return true;
}

/*this function set the valid position to array pointers.*/
chessPosArray* positionsKnightArr(int row, int cul)
{
	int count = 0;

	chessPosArray* pKnightArr;
	pKnightArr = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkMemoryAllocation(pKnightArr);
	pKnightArr->positions = (chessPos*)malloc(8 * sizeof(chessPos));
	checkMemoryAllocation(pKnightArr->positions);

	if (checkValidPos(row + 1, cul + 2))
	{
		pKnightArr->positions[count][0] = row + 1 + 'A';
		pKnightArr->positions[count][1] = cul + 3 + '0';
		count++;
	}

	if (checkValidPos(row + 2, cul + 1))
	{
		pKnightArr->positions[count][0] = row + 2 + 'A';
		pKnightArr->positions[count][1] = cul + 2 + '0';
		count++;
	}

	if (checkValidPos(row - 1, cul - 2))
	{
		pKnightArr->positions[count][0] = row - 1 + 'A';
		pKnightArr->positions[count][1] = cul - 1 + '0';
		count++;
	}

	if (checkValidPos(row - 2, cul - 1))
	{
		pKnightArr->positions[count][0] = row - 2 + 'A';
		pKnightArr->positions[count][1] = cul + '0';
		count++;
	}

	if (checkValidPos(row - 1, cul + 2))
	{
		pKnightArr->positions[count][0] = row - 1 + 'A';
		pKnightArr->positions[count][1] = cul + 3 + '0';
		count++;
	}

	if (checkValidPos(row + 1, cul - 2))
	{
		pKnightArr->positions[count][0] = row + 1 + 'A';
		pKnightArr->positions[count][1] = cul - 1 + '0';
		count++;
	}

	if (checkValidPos(row + 2, cul - 1))
	{
		pKnightArr->positions[count][0] = row + 2 + 'A';
		pKnightArr->positions[count][1] = cul + '0';
		count++;
	}

	if (checkValidPos(row - 2, cul + 1))
	{
		pKnightArr->positions[count][0] = row - 2 + 'A';
		pKnightArr->positions[count][1] = cul + 2 + '0';
		count++;
	}


	if (count == 0)
	{
		pKnightArr->size = 0;
		free(pKnightArr->positions);
		pKnightArr->positions - NULL;
	}
	else
	{
		pKnightArr->positions = (chessPos**)realloc(pKnightArr->positions, count * sizeof(chessPos*));
		checkMemoryAllocation(pKnightArr->positions);
		pKnightArr->size = count;
	}
	return pKnightArr;
}



/*2*/
void display(chessPosList* lst)
{
	deleteDoubleCells(lst);

	int count = 1;
	int row, cul;
	int arr[ROWSIZE][CULSIZE] = { 0 };

	chessPosCell* index;
	index = lst->head;
	while (index != NULL)
	{
		row = (index->position[0]) - 'A';
		cul = (index->position[1]) - '1';
		arr[row][cul] = count;
		count++;
		index = index->next;
	}
	printBoard(arr);
}

/*this function deletes double cells*/
void deleteDoubleCells(chessPosList* lst)
{
	int arr[ROWSIZE][CULSIZE] = { 0 };
	chessPosCell* CPC = lst->head;
	chessPosCell* PrevCPC = lst->head;
	while (CPC != NULL)
	{

		if (arr[CPC->position[0] - 'A'][CPC->position[1] - '1'] == 0)
		{
			arr[CPC->position[0] - 'A'][CPC->position[1] - '1']++;
			PrevCPC = CPC;
			CPC = CPC->next;
		}
		else
		{
			PrevCPC->next = CPC->next;
			free(CPC);
			CPC = PrevCPC->next;
		}
	}
	lst->tail = PrevCPC;
}

/*this function prints the board*/
void printBoard(int arr[][CULSIZE])
{
	char let = 'A';
	int k, i, j;
	printf("     ");
	for (k = 1; k < ROWSIZE + 1; k++)
		printf("  %d  ", k);
	printf("\n\n");
	for (i = 1; i < ROWSIZE + 1; i++)
	{
		printf("  %c  ", let);
		let++;
		for (j = 1; j < CULSIZE + 1; j++)
			printf("  %d  ", arr[i - 1][j - 1]);
		printf("\n\n");
	}
	printf("\n");
}
