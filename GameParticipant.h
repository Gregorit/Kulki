#pragma once
#include "Board.h"

template<typename T1>
class Board;
class GameParticipant
{
public:
	virtual void move(Board<char> &board);
	GameParticipant();
};