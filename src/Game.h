/*
 * Twisty Passages - A simple rogue-like dungeon crawler
 * Copyright (C) 2018  Elliot Dronebarger
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_H_
#define GAME_H_

#include "Level.h"
#include "Display.h"
#include "Monster.h"
#include <ncurses.h>
#include <vector>

const int MAX_LEVELS = 50;

using namespace std;

class Game {
public:
	Game();
	virtual ~Game();
	int start();
	int currentLevel;

	vector<Level> levels;
	Monster character;
	Display disp;

private:
	void processInput(int input);
	void moveCharacter(unsigned int keypadPressed);
	void moveLevel(unsigned int keypadPressed);
};

#endif /* GAME_H_ */
