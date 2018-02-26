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
#include "Square.h"

Square::Square()
{
    //ctor
    square = WALL;
    walkable = false;
    symbol = '#';
    seen = false;
    isVisible = false;
}

Square::~Square()
{
    //dtor
}

bool Square::isWalkable()
{
    return walkable;
}

void Square::setType(squareType s)
{
    square = s;
    switch (square)
    {
        case WALL:
            symbol = '#';
            walkable = false;
            break;
        case HARD_WALL:
            symbol = '#';
            walkable = false;
            break;
        case FLOOR:
            symbol = '.';
            walkable = true;
            break;
        case DOOR_CLOSED:
            symbol = '+';
            walkable = false;
            break;
        case DOOR_OPEN:
            symbol = '/';
            walkable = true;
            break;
        case STAIRS_DOWN:
        	symbol = '>';
        	walkable = true;
        	break;
        case STAIRS_UP:
        	symbol = '<';
        	walkable = true;
        	break;
    }
}
int Square::getType()
{
    return square;
}
char Square::getSymbol()
{
    return symbol;
}
void Square::setSymbol(char c)
{
	symbol = c;
}
