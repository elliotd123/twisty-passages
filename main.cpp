#include <iostream>
#include "Level.h"
#include "Display.h"
#include "Monster.h"
#include "Game.h"

using namespace std;

int main()
{
	Game game = Game();
	int result = game.start();
	return result;
}
