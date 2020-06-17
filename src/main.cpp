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
#include <iostream>

#include "CharacterData.h"
#include "Config.h"
#include "Display.h"
#include "Level.h"
#include "Logger.h"
#include "Monster.h"
#include "Game.h"

using namespace std;

int main()
{
	Config *c = c->getInstance();
	Logger *l = l->getInstance();
	CharacterData *ch = ch->getInstance();

	l->log(Logger::FILE,"Starting game");

	Game game = Game();
	int result = game.start();

	l->log(Logger::FILE|Logger::STDOUT,"Game completed, result: " + std::to_string(result));

	ch->clean();
	l->clean();
	c->clean();
	
	return result;
}
