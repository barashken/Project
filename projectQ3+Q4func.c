#include "projectHeader.h"
#include "projectQ1+Q2header.h"
#include "projectQ3+Q4header.h"


/*3*/

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree resTree;
	chessPosArray*** mathForBoard;

	bool** arrBool;
	arrBool = makeBoolArr(startingPosition);

	mathForBoard = validKnightMoves();
	resTree.root = findAllPossibleKnightPathsHelper(*startingPosition, mathForBoard, arrBool);

	freeArrBool(arrBool);
	freeChessPosArray(mathForBoard);
	return resTree;
}

bool** makeBoolArr(chessPos* startingPosition)
{
	bool** arrBool;
	int i, j;
	arrBool = (bool**)malloc(ROWSIZE * sizeof(bool*));
	checkMemoryAllocation(arrBool);
	for (i = 0; i < ROWSIZE; i++)
	{
		arrBool[i] = (bool*)malloc(CULSIZE * sizeof(bool));
		checkMemoryAllocation(arrBool[i]);
		for (j = 0; j < CULSIZE; j++)
			arrBool[i][j] = false;
	}

	return arrBool;
}

treeNode* findAllPossibleKnightPathsHelper(chessPos curPosition, chessPosArray*** math, bool** route)
{
	int i;
	treeNode* resNode;
	treeNode* child;
	resNode = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(resNode);
	child = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(child);

	if (route[curPosition[0] - 'A'][curPosition[1] - '0' - 1])
		return NULL;

	else
	{
		resNode->position[0] = curPosition[0];
		resNode->position[1] = curPosition[1];
		resNode->next_possible_positions = NULL;


		route[curPosition[0] - 'A'][curPosition[1] - '0' - 1] = true;

		for (i = 0; i < math[curPosition[0] - 'A'][curPosition[1] - '0' - 1]->size; i++)
		{

			child = findAllPossibleKnightPathsHelper(math[curPosition[0] - 'A'][curPosition[1] - '0' - 1]->positions[i], math, route);

			if (child != NULL)
			{
				insertTreeNodeToStartList(child, &resNode->next_possible_positions);
				route[child->position[0] - 'A'][child->position[1] - '0' - 1] = false;

			}

		}
		route[curPosition[0] - 'A'][curPosition[1] - '0' - 1] = false;

		return resNode;
	}
}

void insertTreeNodeToStartList(treeNode* node, treeNodeListCell** list)
{
	treeNodeListCell* newNodeList;
	newNodeList = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(newNodeList);
	newNodeList->node = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(newNodeList->node);

	if (*list == NULL)
	{
		newNodeList->node = node;
		newNodeList->next = NULL;
		*list = newNodeList;
	}

	else
	{
		newNodeList->node = node;
		newNodeList->next = *list;
		*list = newNodeList;
	}
}



/*4*/

/*this function returns the list of Knight Path Covering All Board, if there is no Path Covering All Board function returns null*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	int hight = 0;
	chessPosList* ListPath;

	ListPath = findKnightPathCoveringAllBoardHelper(path_tree->root, &hight);
	if (hight == ROWSIZE * CULSIZE)
		return ListPath;
	else
	{
		freeList(ListPath);
		return NULL;
	}
}

chessPosList* findKnightPathCoveringAllBoardHelper(treeNode* root, int* hight)
{
	int max = 0;
	treeNodeListCell* cur;
	chessPosList* resList;
	chessPosList* listPath;
	resList = makeEmptyList();
	listPath = makeEmptyList();

	if (root == NULL)
	{
		return listPath;
	}
	else
	{
		cur = root->next_possible_positions;
		while (cur != NULL)
		{
			int tempSize = 0;
			listPath = findKnightPathCoveringAllBoardHelper(cur->node, &tempSize);

			if (max < tempSize)
			{
				freeList(resList);
				resList = listPath;
				max = tempSize;
			}
			else
				freeList(listPath);
			cur = cur->next;
		}
		insertChessPosToStartchessPosList(root->position, resList);
		*hight = max + 1;
		return resList;
	}
}

/*this function make empty list*/
chessPosList* makeEmptyList()
{
	chessPosList* list;
	list = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(list);
	list->head = NULL;
	list->tail = NULL;
	return list;
}

/*this function insert new chessPosCell to start chessPosList*/
void insertChessPosToStartchessPosList(chessPos position, chessPosList* ListPath)
{
	chessPosCell* newCell = NULL;
	newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(newCell);

	newCell->position[0] = position[0];
	newCell->position[1] = position[1];

	if (ListPath->head == NULL)
	{
		ListPath->head = newCell;
		ListPath->tail = newCell;
		newCell->next = NULL;
	}
	else
	{
		newCell->next = ListPath->head;
		ListPath->head = newCell;
	}
}

/*this function free chessPosList*/
void freeList(chessPosList* ListPath)
{
	if (ListPath == NULL)
		return;
	chessPosCell* cur = ListPath->head;
	while (ListPath->head != NULL)
	{
		cur = ListPath->head;
		ListPath->head = ListPath->head->next;
		free(cur);
	}
}
