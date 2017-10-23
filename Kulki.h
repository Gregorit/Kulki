#pragma once
#include "Player.h"
#include "Ranking.h"

class Kulki
{
private:
	Board<char> board;
	Player *player;
	Ranking ranking;
public:
	Kulki(); //Balls
	void writeRules();
	void mainMenu();
	~Kulki();
};