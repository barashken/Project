#include "projectHeader.h"

void freeChessPosArray(chessPosArray*** c)
{

	int i, j,h;
	for (i = 0; i < ROWSIZE; i++)
	{
		for (j = 0; j < ROWSIZE; j++)
		{
				free(c[i][j]->positions);
		}
		free(c[i]);
	}
	free (c);
}
void freePosArr(chessPosArray* c)
{
	int i;
	for (i = 0; i < c->size; i++)
	{
		free(c->positions[i]);
	}
}


/*this function free chess pos array*/
void freechessPosArray(chessPosArray*** arr)
{
	int row, cul, numOfPos, size;

	for (row = 0; row < ROWSIZE; row++)
	{
		for (cul = 0; cul < CULSIZE; cul++)
		{
			size = arr[row][cul]->size;
			for (numOfPos = 0; numOfPos < size; numOfPos++)
			{
				free(arr[row][cul]->positions[numOfPos]);
			}
			free(arr[row][cul]);
		}
		free(arr[row]);
	}
	free(arr);
}

/*this function free arr bool*/
void freeArrBool(bool** arr)
{
	int row, cul;

	for (row = 0; row < ROWSIZE; row++)
	{
		for (cul = 0; cul < CULSIZE; cul++)
			free(arr[row][cul]);
		free(arr[row]);
	}
	free(arr);
}

/*this function free tree*/
void freeTree(treeNode* root)
{
	if (root == NULL)
		return;

	if (root->next_possible_positions == NULL)
	{
		free(root);
		return;
	}

	treeNodeListCell* cur;
	treeNodeListCell* temp = root->next_possible_positions;

	while (temp)
	{
		cur = temp->next;
		freeTree(temp->node);
		free(temp);
		temp = cur;
	}

	free(root);
}

/*check memory allocation*/
void checkMemoryAllocation(void* arr)
{
	if (arr == NULL)
	{
		puts("A memory allocation error");
		exit(1);
	}
}