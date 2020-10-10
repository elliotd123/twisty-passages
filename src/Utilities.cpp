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
#include "Utilities.h"

Coord::Coord()
{
	x = 0;
	y = 0;
}
Coord::Coord(int inX, int inY)
{
	x = inX;
	y = inY;
}
Coord::~Coord()
{

}



Dimension::Dimension()
{
	x = 0;
	y = 0;
}

Dimension::Dimension(int inX, int inY)
{
	x = inX;
	y = inY;
}

Dimension::~Dimension()
{

}

Random::Random()
{
	l = l->getInstance();
	time_t seconds;
	seconds = time(NULL);
	l->log(Logger::FILE, "Random seed: " + std::to_string(seconds));
	srand(seconds);
}

Random::Random(int seed) {
	l = l->getInstance();
	l->log(Logger::FILE, "Random seed: " + std::to_string(seed));
	srand(seed);
}

Random::~Random()
{

}

int Random::getInt(int min, int max)
{
	int rand_int = (rand()%(max+1-min) + min);
	return rand_int;
}
