#pragma once
//#pragma warning (disable : 4996) //uzyc gdyby byly problemy z fopen

//Defines for cleaning terminal/commandline which supports multiple systems
#ifdef _WIN32 //For Windows OS
#define CLEAR "cls"
#else //Any other OS
#define CLEAR "clear"
#endif

#include <iostream>
#include <ctime>
#include "GameParticipant.h"
#define BOARD_ARRAY 9
#define MAX 17
#define RANDOMS_AMOUNT 3
using namespace std;

class GameParticipant;

template<typename T1>
class Board
{
private:
	T1 arr[BOARD_ARRAY][BOARD_ARRAY];
	char kulkaType[RANDOMS_AMOUNT]; //ball type
public:
	friend class Player;
	Board()
	{
		/** GENERATING EMPTY BOARD **/
		for (int i = 0; i < BOARD_ARRAY; i++)
		for (int j = 0; j < BOARD_ARRAY; j++)
			arr[i][j] = ' ';		
	}

	void drawingKulki() //drawing balls
	{
		int i;
		int j;
		srand(time(NULL));

		for (int amountOfRandomKulki = 0; checkGameOver() && amountOfRandomKulki < RANDOMS_AMOUNT; amountOfRandomKulki++) //amount of new random balls
		{
			kulkaType[amountOfRandomKulki] = rand() % 7 + 'A';
			i = rand() % BOARD_ARRAY;
			j = rand() % BOARD_ARRAY;

			while (arr[i][j] != ' ')
			{
				i = rand() % BOARD_ARRAY;
				j = rand() % BOARD_ARRAY;
			}
			arr[i][j] = kulkaType[amountOfRandomKulki];
		}
	}

	void nextKulkiPreview() //next balls preview
	{
		cout << "NEXT KULKI (balls): ";
		for (int amountOfRandomKulki = 0; amountOfRandomKulki < RANDOMS_AMOUNT; amountOfRandomKulki++)
			cout << kulkaType[amountOfRandomKulki] << " ";
		cout << endl;
	}

	void drawingNextKulki() //drawing next balls
	{
		srand(time(NULL));

		for (int amountOfRandomKulki = 0; amountOfRandomKulki < RANDOMS_AMOUNT; amountOfRandomKulki++)
			kulkaType[amountOfRandomKulki] = rand() % 7 + 'A';
	}

	void insertingNextKulki()
	{
		int i;
		int j;
		srand(time(NULL));

		for (int amountOfRandomKulki = 0; checkGameOver() && amountOfRandomKulki < RANDOMS_AMOUNT; amountOfRandomKulki++)
		{
			i = rand() % BOARD_ARRAY;
			j = rand() % BOARD_ARRAY;

			while (arr[i][j] != ' ')
			{
				i = rand() % BOARD_ARRAY;
				j = rand() % BOARD_ARRAY;
			}
			arr[i][j] = kulkaType[amountOfRandomKulki];
		}
	}
	
	bool checkGameOver()
	{
		int emptyFieldsCounter = 0;
		for (int i = 0; i < BOARD_ARRAY; i++)
		for (int j = 0; j < BOARD_ARRAY; j++)
		{
			if (arr[i][j] == ' ')
				emptyFieldsCounter++;
		}
		if (emptyFieldsCounter == 0)
			return false;
		else
			return true;
	}

	int linesDetection() //includes points calculations
	{
		int counter = 0;
		int points = 0;
		int removalArray[BOARD_ARRAY][BOARD_ARRAY] = { 0 };	//for cross removal and points calculation

		/** HORIZONTAL **/
		for (int i = 0; i < BOARD_ARRAY; i++)
		{
			for (int j = 0; j < BOARD_ARRAY; j++)
			{
				if (counter >= 4 && (j == BOARD_ARRAY - 1 || arr[i][j] != arr[i][j + 1]))
				{
					for (; counter >= 0; counter--)
						removalArray[i][j - counter]++;
				}
				if (j != BOARD_ARRAY - 1 && arr[i][j] == arr[i][j + 1] && arr[i][j] != ' ')
					counter++;
				else
					counter = 0;
			}
			counter = 0;
		}

		/** VERTICAL **/
		for (int j = 0; j < BOARD_ARRAY; j++)
		{
			for (int i = 0; i < BOARD_ARRAY; i++)
			{
				if (counter >= 4 && (i == BOARD_ARRAY - 1 || arr[i][j] != arr[i+1][j]))
				{
					for (; counter >= 0; counter--)
						removalArray[i - counter][j]++;
				}
				if (i != BOARD_ARRAY - 1 && arr[i][j] == arr[i + 1][j] && arr[i][j] != ' ')
					counter++;
				else
					counter = 0;
			}
			counter = 0;
		}

		/** OBLIQUE UP-RIGHT **/
		for (int i = 0; i < BOARD_ARRAY; i++)
		{
			for (int j = 0; j < BOARD_ARRAY; j++)
			{
				if (counter >= 4 && (i + j >= BOARD_ARRAY - 1 || arr[j][j + i] != arr[j + 1][j + i + 1]))
				{
					for (; counter >= 0; counter--)
						removalArray[j - counter][j + i - counter]++;
				}
				if (i + j < BOARD_ARRAY - 1 && arr[j][j + i] == arr[j + 1][j + i + 1] && arr[j][j + i] != ' ')
					counter++;
				else
					counter = 0;
			}
			counter = 0;
		}

		/** OBLIQUE DOWN-RIGHT **/
		for (int i = 1; i < BOARD_ARRAY; i++)
		{
			for (int j = 0; j < BOARD_ARRAY; j++)
			{
				if (counter >= 4 && (i + j >= BOARD_ARRAY - 1 || arr[j + i][j] != arr[j + i + 1][j + 1]))
				{
					for (; counter >= 0; counter--)
						removalArray[j + i - counter][j - counter]++;
				}
				if (i + j < BOARD_ARRAY - 1 && arr[j + i][j] == arr[j + i + 1][j + 1] && arr[j + i][j] != ' ')
					counter++;
				else
					counter = 0;
			}
			counter = 0;
		}

		/** OBLIQUE UP-LEFT **/
		for (int i = BOARD_ARRAY-1; i > 0; i--)
		{ 
			for (int j = 0; j < BOARD_ARRAY; j++)
			{
				if (counter >= 4 && (i - j <= 0 || j >= BOARD_ARRAY - 1 || arr[j][i - j] != arr[j + 1][i - j - 1]))
				{
					for (; counter >= 0; counter--)
						removalArray[j - counter][i - j + counter]++;
				}
				if (i - j > 0 && j < BOARD_ARRAY - 1 && arr[j][i - j] == arr[j + 1][i - j - 1] && arr[j][i - j] != ' ')
					counter++;
				else
					counter = 0;
			}
			counter = 0;
		}

		/** OBLIQUE DOWN-LEFT **/
		for (int i = BOARD_ARRAY - 2; i > 0; i--)
		{
			for (int j = 0; j < BOARD_ARRAY; j++)
			{
				if (counter >= 4 && ((BOARD_ARRAY - 1 - i) + j < BOARD_ARRAY - 1 || BOARD_ARRAY - 1 - j == 0 || arr[(BOARD_ARRAY - 1 - i) + j][BOARD_ARRAY - 1 - j] != arr[(BOARD_ARRAY - 1 - i) + j + 1][BOARD_ARRAY - 1 - j - 1]))
				{
					for (; counter >= 0; counter--)
						removalArray[(BOARD_ARRAY - 1 - i) + j - counter][BOARD_ARRAY - 1 - j + counter]++;
				}
				if ((BOARD_ARRAY - 1 - i) + j > BOARD_ARRAY - 1 && BOARD_ARRAY - 1 - j != 0 && arr[(BOARD_ARRAY - 1 - i) + j][BOARD_ARRAY - 1 - j] == arr[(BOARD_ARRAY - 1 - i) + j + 1][BOARD_ARRAY - 1 - j - 1] && arr[(BOARD_ARRAY - 1 - i) + j][BOARD_ARRAY - 1 - j] != ' ')
					counter++;
				else
					counter = 0;
			}
			counter = 0;
		}

		/** KULKI REMOVAL FROM BOARD **/
		for (int i = 0; i < BOARD_ARRAY; i++)
			for (int j = 0; j < BOARD_ARRAY; j++)
			{
				if (removalArray[i][j] > 0)
				{
					arr[i][j] = ' ';
					points += removalArray[i][j];
				}
			}
		return points;
	}

	void saveBoard(int points)
	{
		FILE *boardSave;
		boardSave = fopen("board.txt", "w");
		for (int i = 0; i < BOARD_ARRAY; i++)
		for (int j = 0; j < BOARD_ARRAY; j++)
		{
			if (arr[i][j] == ' ')
				fprintf(boardSave, "_");
			else
				fprintf(boardSave, "%c", arr[i][j]);
		}
		for (int i = 0; i < RANDOMS_AMOUNT; i++)
			fprintf(boardSave, "%c", kulkaType[i]);
		fprintf(boardSave, "%d", points);
		fclose(boardSave);
	}

	int loadBoard()
	{
		int points;
		FILE *boardLoad;
		boardLoad = fopen("board.txt", "r");
		if (boardLoad == NULL)
			return -1;
		for (int i = 0; i < BOARD_ARRAY; i++)
		for (int j = 0; j < BOARD_ARRAY; j++)
		{
			fscanf(boardLoad, "%c", &arr[i][j]);
			if (arr[i][j] == '_')
				arr[i][j] = ' ';
		}
		for (int i = 0; i < RANDOMS_AMOUNT; i++)
			fscanf(boardLoad, "%c", &kulkaType[i]);
		fscanf(boardLoad, "%d", &points);
		fclose(boardLoad);
		return points;
	}
	
	void write()
	{
		char letter = 65;
		int number = 0;

		system(CLEAR);
		cout << "  ";
		for (int i = 0; i < (MAX / 2) + 1; i++)
		{
			cout << letter << "   ";
			letter++;
		}
		cout << endl;
		for (int i = 0; i < MAX; i++)
		{
			if (i % 2 == 0)
			{
				cout << number << " ";
				number++;
			}
			for (int j = 0; j < MAX; j++)
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
						cout << arr[i / 2][j / 2];
					else
						cout << " - ";
				}
				else
				{
					if (j == 0)
						cout << "  ";
					if (j % 2 == 0)
						cout << "| ";
					else
						cout << "  ";
				}
			}
			cout << endl;
		}
	}
};