//Defines for cleaning terminal/commandline which supports multiple systems
#ifdef _WIN32 //For Windows OS
#define CLEAR "cls"
#else //Any other OS
#define CLEAR "clear"
#endif

#include <iostream>
#include "Kulki.h"
using namespace std;

Kulki::Kulki() : player(new Player()) {} //default constructor

void Kulki::writeRules()
{
	system(CLEAR);
	cout << "RULES OF KULKI:" << endl;
	cout << "The purpose of the game is to match kulki (balls) in the lines. The lines" << endl;
	cout << "must contain same type of minimum 5 kulki and they can be horizontal," << endl;
	cout << "vertical and oblique." << endl << endl;
	cout << "After creating a appropriate line it's disappear and it gives points." << endl;
	cout << "The game starts with 3 kulki placed randomly on board." << endl;
	cout << "Round ends when we do not perform line disappear." << endl;
	cout << "After that on board the new kulki will show up." << endl << endl;
	cout << "Kulki can move only horizontal and vertical. It's not possible" << endl;
	cout << "to infiltrate by other kulki - they act like a wall." << endl;
	cout << "So it's possible to make some fields unavailable for certain kulki type - " << endl;
	cout << "in this case the move is forbidden." << endl << endl;
	cout << "Points are awarded in the following way:" << endl;
	cout << ">A normal kulka in line - 1 point," << endl;
	cout << ">Kulka which connects more than one line (multiple disappear) - *~2-7 points." << endl;
	cout << "    *it depends how many lines were created by that kulka" << endl << endl;
	cout << "The game is over when no fields on board are empty." << endl << endl << endl;
	cout << "Press Enter to return to the main menu.";
	cin.ignore().get(); //waiting for input
}

void Kulki::mainMenu()
{
	string playerName;
	int pointsAuxiliary = 0;
	int choice;
	int choiceConfirmation = 0;	//a counter that checks confirmation of choice when exiting the game
	while (choiceConfirmation != 1)
	{
		system(CLEAR);
		cout << "\t    ~~~~~~ KULKI ~~~~~~" << endl;
		cout << "\t   AUTHOR: GRZEGORZ URYCH\n\n" << endl;
		cout << "       +++++++++++++++++++++++++++++" << endl;
		cout << "       ++        MAIN MENU:       ++\n       +++++++++++++++++++++++++++++" << endl;
		cout << "       ++(1)New game\t\t  ++\n       ++(2)Load last game\t  ++\n       ++(3)Rules\t\t  ++\n       ++(4)Scoreboard\t\t  ++" << endl;
		cout << "       +++++++++++++++++++++++++++++" << endl;
		cout << "       ++(0)Exit from game\t  ++\n       +++++++++++++++++++++++++++++" << endl << endl;
		cout << "\t       Your choose: ";
		cin >> choice;
		switch (choice)
		{
		case 1:	//new game
				player->setPoints(0); //resetting points for new game

				/** THE GAME **/
				board.drawingKulki();
				while (board.checkGameOver() != false)
				{
					board.drawingNextKulki();
					do
					{
						board.write();
						board.nextKulkiPreview();
						cout << "Points: " << player->getPoints() << endl << endl;
						player->move(board);
						pointsAuxiliary = board.linesDetection();
						player->addPoints(pointsAuxiliary);
						board.saveBoard(player->getPoints());
					} while (pointsAuxiliary > 0);
					board.insertingNextKulki();
					player->addPoints(board.linesDetection());
				}

				/** ADDING TO THE RANKING **/
				board.write();
				cout << "GAME OVER" << endl << endl;
				cout << "Give your name: ";
				cin >> playerName;
				ranking.add(playerName, player->getPoints());
				cout << "Press Enter to return to the main menu.";
				cin.ignore().get(); //waiting for input
				break;
		case 2:	//loading save file
			player->setPoints(board.loadBoard());

			/** CHECKING THE FILE **/
			if (board.checkGameOver() != true)
			{
				cout << "This save includes already ended game." << endl;
				cout << "Returning to the main menu..." << endl << endl;
				cout << "Press Enter to continue.";
				cin.ignore().get(); //waiting for input
				break;
			}
			if (player->getPoints() < 0)
			{
				cout << "No save file." << endl;
				cout << "Returning to the main menu..." << endl << endl;
				cout << "Press Enter to continue.";
				cin.ignore().get(); //waiting for input
				break;
			}
			cout << "Save has been loaded successfully." << endl;
			cout << "Press Enter to continue.";
			cin.ignore().get(); //waiting for input

			/** THE GAME **/
			while (board.checkGameOver() != false)
			{
				do
				{
					board.write();
					board.nextKulkiPreview();
					cout << "Points: " << player->getPoints() << endl << endl;
					player->move(board);
					pointsAuxiliary = board.linesDetection();
					player->addPoints(pointsAuxiliary);
					board.saveBoard(player->getPoints());
				} while (pointsAuxiliary > 0);
				board.insertingNextKulki();
				player->addPoints(board.linesDetection());
				board.drawingNextKulki();
			}

			/** ADDING TO THE RANKING **/
			board.write();
			cout << "GAME OVER" << endl << endl;
			cout << "Give your name: ";
			cin >> playerName;
			ranking.add(playerName, player->getPoints());
			cout << "Press Enter to return to the main menu.";
			cin.ignore().get(); //waiting for input
			break;
		case 3:	//rules
			writeRules();
			break;
		case 4:
			system(CLEAR);
			cout << "SCOREBOARD:" << endl;
			cout << "[Name, points]" << endl << endl;
			ranking.write();
			cout << endl << "Press Enter to return to the main menu.";
			cin.ignore().get(); //waiting for input
			break;
		case 0:	//exit from program
			system(CLEAR);
			cout << "Are you sure to exit the program?\n[(1)Yes, (0)No]: ";
			cin >> choiceConfirmation;
			if (choiceConfirmation == 1)
			{
				cout << "\nSee you soon. Thanks for playing." << endl;
				break;
			}
		}
	}
}

Kulki::~Kulki()
{
	delete player;
}
