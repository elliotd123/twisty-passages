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
#include "Game.h"

Game::Game() {
	c = c->getInstance();
	currentLevel = 0;
	character = Character();
	disp = Display();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

int Game::start()
{
	levels.push_back(Level());
	character.location = levels[0].rooms[0].center;
	levels[currentLevel].updateVisible(character.location);
	disp.drawLevel(levels[currentLevel]);
	disp.drawItems();
	disp.drawMonster(levels[currentLevel],character);
	disp.drawMonsters(levels[currentLevel],levels[currentLevel].monsters);
	disp.drawCharStats(character);
	disp.moveCursor(Coord(0,0));

	int c;
	while ((c = disp.getInput()) != 'q')
	{
		processInput(c);
		levels[currentLevel].updateVisible(character.location);
		disp.drawLevel(levels[currentLevel]);
		disp.drawItems();
		disp.drawMonster(levels[currentLevel],character);
		disp.drawMonsters(levels[currentLevel],levels[currentLevel].monsters);
		disp.drawCharStats(character);
		disp.moveCursor(Coord(0,0));
	}
	return 0;
}

//Process an input command
void Game::processInput(int input)
{
	string output = "";
	switch (input)
	{

		//First we will check if the player pressed a keypad or number, indicating they want to move
		case KEY_UP: case '8': case KEY_RIGHT: case '6': case KEY_DOWN: case '2':
		case KEY_LEFT: case '4': case KEY_A1: case '7': case KEY_C1: case '1':
		case KEY_C3: case '3': case KEY_A3: case '9': case KEY_B2: case '5':
			moveCharacter(input);
			break;

		case '<': case '>':
			moveLevel(input);
			break;

		//TODO: all other commands will be processed here

		default:
			break;
	}
}

//Process a move command and move/don't move/attack as necessary.
void Game::moveCharacter(unsigned int keypadPressed)
{
	Coord moveTo = character.location;
	switch (keypadPressed)
		{
			case KEY_UP: case '8':
				moveTo.y--;
				break;
			case KEY_RIGHT: case '6':
				moveTo.x++;
				break;
			case KEY_DOWN: case '2':
				moveTo.y++;
				break;
			case KEY_LEFT: case '4':
				moveTo.x--;
				break;
			case KEY_A1: case '7':
				moveTo.x--;
				moveTo.y--;
				break;
			case KEY_C1: case '1':
				moveTo.x--;
				moveTo.y++;
				break;
			case KEY_C3: case '3':
				moveTo.x++;
				moveTo.y++;
				break;
			case KEY_A3: case '9':
				moveTo.x++;
				moveTo.y--;
				break;
			case KEY_B2: case '5':
				break;
			default:
				break;
		}

	//Check if the space has a monster on it. If so, attack it.
	if (levels[currentLevel].isMonster(moveTo))
	{
		//TODO: Character hit a monster. Do an attack.
	}

	//Check to see if this is a space that can be walked on. If so, move the character to it
	else if (levels[currentLevel].squares[moveTo.x][moveTo.y].isWalkable())
	{
		character.location = moveTo;
	}
}

void Game::moveLevel(unsigned int keypadPressed)
{
	switch (keypadPressed)
	{
		case '<':
			if (currentLevel > 0 && (levels[currentLevel].squares[character.location.x][character.location.y].getType() == STAIRS_UP))
			{
				currentLevel--;
				character.location.x = levels[currentLevel].rooms[levels[currentLevel].rooms.size()-1].center.x;
				character.location.y = levels[currentLevel].rooms[levels[currentLevel].rooms.size()-1].center.y;
				disp.clearScreen();
			}
			break;
		case '>':
			if (currentLevel < ((int) c->getInt("MAX_LEVELS") - 1) && (levels[currentLevel].squares[character.location.x][character.location.y].getType() == STAIRS_DOWN))
			{
				if ((currentLevel+1) > (levels.size()-1))
					levels.push_back(Level());
				currentLevel++;
				character.location.x = levels[currentLevel].rooms[0].center.x;
				character.location.y = levels[currentLevel].rooms[0].center.y;
				disp.clearScreen();
			}
			break;
		default:
			break;
	}
}
