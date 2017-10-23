#pragma once
#include "GameParticipant.h"
#include "Board.h"

class Player : public GameParticipant
{
private:
	int points;
	int toI;
	int toJ;
	bool endOfVisit;
	bool auxiliaryArray[BOARD_ARRAY][BOARD_ARRAY];
public:
	Player();
	void setPoints(int point);
	int getPoints();
	void addPoints(int poi); //poi - points
	void move(Board<char> &board);
	void visit(int i, int j);
	bool checkPossibleMove(Board<char> &board, int fromI, int fromJ);
};