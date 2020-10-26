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
#include "CharacterData.h"
#include "Fight.h"
#include "Game.h"
#include "Logger.h"

Game::Game() {
	c = c->getInstance();
	currentLevel = 0;
	CharacterData *ch = ch->getInstance();
	//TODO: We'll have to restructure this at some point to allow other character types
	character = ch->getCharacterByName("swordsman");

	Logger * l = l->getInstance();

	std::vector<Character> characters = ch->getCharacters();
	
	std::string chs = "\nList of available characters:\n";
	for (int i = 0; i < characters.size(); i++) {
		chs += "\t" + characters[i].keyname + "\n";
	}

	l->log(Logger::FILE, chs);
	
	this->disp = new Display();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
	delete(disp);
}

int Game::start()
{
	levels.push_back(Level());
	levels[0].addMonsters(0);
	character.location = levels[0].rooms[0].center;
	redrawGameWindow();

	int c;
	//Main Loop
	while ((c = getInput()) != SDLK_q)
	{
		processInput(c);
		for (int i = 0; i < levels[currentLevel].monsters.size(); i++) {
			levels[currentLevel].monsters[i].takeTurn(levels[currentLevel],character);
		}
		character.update();
		if (character.hp <= 0.0) {
			//TODO: Add a message and true end of game
			break;
		}
		redrawGameWindow();
	}
	return 0;
}
void Game::redrawGameWindow() {
	levels[currentLevel].updateVisible(character);
	disp->clearScreen();
	disp->drawLevel(levels[currentLevel]);
	disp->drawItems();
	disp->drawMonster(levels[currentLevel],character);
	disp->drawMonsters(levels[currentLevel],levels[currentLevel].monsters,character);
	disp->drawCharStats(character);
	disp->drawLevelNumber(currentLevel);
	disp->redraw();
}

//Process an input command
void Game::processInput(int input)
{
	string output = "";
	switch (input)
	{

		//First we will check if the player pressed a keypad or number, indicating they want to move
		case SDLK_UP: case SDLK_RIGHT: case SDLK_DOWN: case SDLK_LEFT: 
		case SDLK_KP_1: case SDLK_KP_2: case SDLK_KP_3:
		case SDLK_KP_4: case SDLK_KP_5: case SDLK_KP_6:
		case SDLK_KP_7: case SDLK_KP_8: case SDLK_KP_9:
			moveCharacter(input);
			break;

		case SDLK_LESS: case SDLK_GREATER:
		case SDLK_KP_LESS: case SDLK_KP_GREATER:
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
			case SDLK_KP_8: SDLK_UP:
				moveTo.y--;
				break;
			case SDLK_KP_6: SDLK_RIGHT:
				moveTo.x++;
				break;
			case SDLK_KP_2: SDLK_DOWN:
				moveTo.y++;
				break;
			case SDLK_KP_4: SDLK_LEFT:
				moveTo.x--;
				break;
			case SDLK_KP_7:
				moveTo.x--;
				moveTo.y--;
				break;
			case SDLK_KP_1:
				moveTo.x--;
				moveTo.y++;
				break;
			case SDLK_KP_3:
				moveTo.x++;
				moveTo.y++;
				break;
			case SDLK_KP_9:
				moveTo.x++;
				moveTo.y--;
				break;
			case SDLK_KP_5:
				break;
			default:
				break;
		}

	//Check if the space has a monster on it. If so, attack it.
	Monster * m = levels[currentLevel].monsterAt(moveTo);
	if (m)
	{
		Fight::attack(character,*m);

		if (m->hp <= 0.0) {
			for (int i = 0; i < levels[currentLevel].monsters.size(); i++) {
				if (m == &levels[currentLevel].monsters[i]) {
					levels[currentLevel].monsters.erase(levels[currentLevel].monsters.begin() + i);
				}
			}
		}
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
		case SDLK_LESS: case SDLK_KP_LESS:
			if (currentLevel > 0 && (levels[currentLevel].squares[character.location.x][character.location.y].getType() == STAIRS_UP))
			{
				currentLevel--;
				character.location.x = levels[currentLevel].rooms[levels[currentLevel].rooms.size()-1].center.x;
				character.location.y = levels[currentLevel].rooms[levels[currentLevel].rooms.size()-1].center.y;
				disp->clearScreen();
			}
			break;
		case SDLK_GREATER: case SDLK_KP_GREATER:
			if (currentLevel < ((int) c->getInt("MAX_LEVELS") - 1) && (levels[currentLevel].squares[character.location.x][character.location.y].getType() == STAIRS_DOWN))
			{
				if ((currentLevel+1) > (levels.size()-1)) {
					levels.push_back(Level());
					levels[currentLevel+1].addMonsters(currentLevel+1);
				}
				currentLevel++;
				character.location.x = levels[currentLevel].rooms[0].center.x;
				character.location.y = levels[currentLevel].rooms[0].center.y;
				disp->clearScreen();
			}
			break;
		default:
			break;
	}
}

//Spinwait for input from user (Sleeping occasionally) and returning the SDL keycode when they give input.
int Game::getInput()
{
	while (true) {
		SDL_Event event;
		
		while( SDL_PollEvent( &event ) ){
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch( event.type ) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_LSHIFT:
					case SDLK_RSHIFT:
					    input_shift = true;
						continue;
						break;
					case SDLK_PERIOD:
						if (input_shift) {
							return SDLK_GREATER;
						}
						break;
					case SDLK_COMMA:
						if (input_shift) {
							return SDLK_LESS;
						}
						break;
					default:
						break;
				}
				return event.key.keysym.sym;
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_LSHIFT:
					case SDLK_RSHIFT:
						input_shift = false;
						break;
					default:
						break;
				}
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						redrawGameWindow();
						break;
					default:
						break;
				}
				break;
			default:
				break;
			}
		}
		SDL_Delay(20);
	}
	return 0;
}