#include <iostream>
#include <limits> //it's needed to make this line works in gcc: cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include "Player.h"
using namespace std;

Player::Player() : GameParticipant(), points(0) {}

void Player::setPoints(int poi)
{
	points = poi;
}

int Player::getPoints()
{
	return points;
}

void Player::addPoints(int poi)
{
	points += poi;
}

void Player::visit(int i, int j) //i, j - where is chosen kulka (ball coordinates)
{
	if (toI == i && toJ == j)
		endOfVisit = true;
	auxiliaryArray[i][j] = true;
	if (endOfVisit != true && i != 0 && auxiliaryArray[i - 1][j] != true)
		visit(i - 1, j);
	if (endOfVisit != true && i != BOARD_ARRAY - 1 && auxiliaryArray[i + 1][j] != true)
		visit(i + 1, j);
	if (endOfVisit != true && j != 0 && auxiliaryArray[i][j - 1] != true)
		visit(i, j - 1);
	if (endOfVisit != true && j != BOARD_ARRAY - 1 && auxiliaryArray[i][j + 1] != true)
		visit(i, j + 1);
}

bool Player::checkPossibleMove(Board<char> &plansza, int zI, int zJ) //false - not visited, true - visited
{
	endOfVisit = false;
	for (int i = 0; i < BOARD_ARRAY; i++)
	for (int j = 0; j < BOARD_ARRAY; j++)
	{
		if (plansza.arr[i][j] != ' ')
			auxiliaryArray[i][j] = true;
		else
			auxiliaryArray[i][j] = false;
	}
	visit(zI, zJ);
	return endOfVisit;
}

void Player::move(Board<char> &board)
{
	char fromI;
	int fromJ;
	char toI;
	int toJ;
	bool okCheck = false;

	while (okCheck != true)
	{
		cout << "Give kulka coordinates, which you want to make a move" << endl << "(how to?: Letter Number): ";
		cin >> fromI;
		cin.clear();
		cin >> fromJ;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //deleting from stream cin all incorrect characters
		if (fromI < 'A' || fromI > 'A' + BOARD_ARRAY || fromJ < 0 || fromJ > BOARD_ARRAY || board.arr[fromJ][fromI - 'A'] == ' ')
		{
			fromI = 'z';
			fromJ = -999;
			cout << endl << "*****************************************************" << endl;
			cout << "**            The field chosen by you:             **" << endl;
			cout << "*****************************************************" << endl;
			cout << "**   #contains an empty field,\t\t\t   **" << endl << "**\tor\t\t\t\t\t   **" << endl << "**   #field was inputted incorrectly.\t\t   **" << endl;
			cout << "*****************************************************" << endl;
			cout << "** Try again." << endl << endl;
			continue;
		}

		cout << "Give coordinates of empty field for making a move: ";
		cin >> toI;
		cin.clear();
		cin >> toJ;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //deleting from stream cin all incorrect characters
						   //in VS '13: cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (toI < 'A' || toI > 'A' + BOARD_ARRAY || toJ < 0 || toJ > BOARD_ARRAY || board.arr[toJ][toI - 'A'] != ' ')
		{
			toI = 'z';
			toJ = -999;
			cout << endl << "*****************************************************" << endl;
			cout << "**            The field chosen by you:             **" << endl;
			cout << "*****************************************************" << endl;
			cout << "**   #is not an empty field,\t\t\t  **" << endl << "**\tor\t\t\t\t\t   **" << endl << "**   #field was inputted incorrectly.\t\t   **" << endl;
			cout << "*****************************************************" << endl;
			cout << "** Try again." << endl << endl;
			continue;
		}

		Player::toI = toJ;
		Player::toJ = toI - 'A';
		if (checkPossibleMove(board, fromJ, fromI - 'A') == true)
		{
			board.arr[toJ][toI - 'A'] = board.arr[fromJ][fromI - 'A'];
			board.arr[fromJ][fromI - 'A'] = ' ';
			okCheck = true;
		}
		else
		{
			cout << endl << "*****************************************************" << endl;
			cout << "**            The field chosen by you:             **" << endl;
			cout << "*****************************************************" << endl;
			cout << "**   #is not an empty field,\t\t\t  **" << endl << "**\tor\t\t\t\t\t   **" << endl << "**   #kulka cannot move on chosen field, **" << endl << "**\tor\t\t\t\t\t   **" << endl << "**   #field was inputted incorrectly.\t\t   **" << endl;
			cout << "*****************************************************" << endl;
			cout << "** Try again." << endl << endl;
		}
	}
}
