/*
 * Utilities.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: elliot
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
	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
}

Random::~Random()
{

}

int Random::getInt(int min, int max)
{
	int rand_int = (rand()%(max-min) + min);
	return rand_int;
}
