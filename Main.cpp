#include "Kulki.h"

int main()
{
	Kulki *game = new Kulki();
	game->mainMenu();
	delete game;
	return 0;
}