/*
 * Twisty Passages - A simple rogue-like dungeon crawler
 * Copyright (C) 2026  Elliot Dronebarger
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

double distance(const Coord& coord1, const Coord& coord2) {
	double result = sqrt((pow(coord2.x-coord1.x,2)) + (pow(coord2.y-coord1.y,2)));
	return result;
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
	if (min == max) {
		return min;
	}
	int rand_int = (rand()%(max+1-min) + min);
	return rand_int;
}

int Random::dice_roll(int num_dice, int dice_size) {
	int total = 0;
	if (num_dice < 1 || dice_size < 2) {
		return 0;
	}
	for (int i = 0; i < num_dice; i++) {
		total += getInt(1,dice_size);
	}
	return total;
}