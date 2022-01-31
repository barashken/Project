#include "projectHeader.h"
#include "projectQ1+Q2header.h"
#include "projectQ3+Q4header.h"
#include "projectQ5+Q6header.h"
#include "projectQ7header.h"


/*7*/

/*print menu function*/
int printMenu()
{
	int choice;

	printf("Please enter your choice: \n\n"
		"1.	Enter a knight's starting position\n"
		"2.	Create all possible knight paths\n"
		"3.	Find a knight path covering all board\n"
		"4.	Save knight path covering all board to file\n"
		"5.	Load and display path from file\n"
		"6.	Exit\n\n");

	scanf("%d", &choice);
	return(choice);
}

/*menu function*/
void menu()
{
	int choice;
	choice = printMenu();
	char letChoice, numChoice;
	chessPos startPos = { '0','0' };
	chessPosList* list = makeEmptyList();
	char* nameOfFile;
	int res=0;
	pathTree tr;	
	tr.root = NULL;

	while (choice != 6)
	{
		switch (choice)
		{
		case(1):
			printf("please enter your start position\n");
			getchar();
			scanf("%c%c", &startPos[0], &startPos[1]);

			while (checkValidPos(startPos[0] - 'A', startPos[1] - '1') == false)
			{
				printf("the position is not valid\n");
				printf("please enter your start position\n");
				getchar();
				scanf("%c%c", &startPos[0], &startPos[1]);
			}
			break;

		case(2):
			if (startPos[0] == '0')
				printf("You need to enter position before choosing 2\n");
			else
				tr = findAllPossibleKnightPaths(&startPos);
			break;

		case(3):
			if (startPos[0] == '0')
				printf("You need to enter position before choosing 3\n");
			else
			{
				if (tr.root == NULL)
					tr = findAllPossibleKnightPaths(&startPos);
				list = findKnightPathCoveringAllBoard(&tr);
				if (list == NULL)
					printf("the route is not valid or not exists\n");
			}
			break;

		case(4):
			if (startPos[0] == '0')
				printf("You need to enter position before choosing 4\n");
			else
			{
				printf("please enter file name\n");
				if (tr.root == NULL)
					tr = findAllPossibleKnightPaths(&startPos);
				if (list == NULL)
					list = findKnightPathCoveringAllBoard(&tr);
				if (list == NULL)
					printf("the route is not valid or not exists\n");
				else
				{
					nameOfFile = createNameOfFile();
					saveListToBinFile(nameOfFile, list);
				}
				freeTree(tr.root);
			}
			break;

		case(5):
			printf("please enter file name to open\n");
			nameOfFile = createNameOfFile();
			res = checkAndDisplayPathFromFile(nameOfFile);
			free(nameOfFile);
			break;

		
		default:
			printf("Your choice is not valid");
			break;
		}

		choice = printMenu();
	}
	exit(1);
}

/*this function get name of file from the user*/
char* createNameOfFile()
{
	char* nameOfFile;
	char ch;
	int phisicalSize = 1, logicalSize = 0;

	nameOfFile = (char*)malloc(phisicalSize * sizeof(char));
	checkMemoryAllocation(nameOfFile);
	
	ch = getchar();
	while (ch == '\n') /*for enters, the last input will be the first character of the name*/
		ch = getchar();
	
	while (ch != ' ' && ch != '\n' && ch != '\t')
	{
		nameOfFile[logicalSize] = ch;
		logicalSize++;
		if (logicalSize == phisicalSize)
		{
			phisicalSize *= 2;
			nameOfFile = (char*)realloc(nameOfFile, phisicalSize * sizeof(char));
			checkMemoryAllocation(nameOfFile);
		}
		ch = getchar();
	}
	nameOfFile[logicalSize] = '\0';

	nameOfFile = (char*)realloc(nameOfFile, (logicalSize + 1) * sizeof(char));
	checkMemoryAllocation(nameOfFile);

	return nameOfFile;
}


