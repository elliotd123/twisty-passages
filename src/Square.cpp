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
#include "Square.h"

Square::Square()
{
    //ctor
    square = WALL;
    walkable = false;
    symbol = squareChar[square];
    seen = false;
    isVisible = false;
}

Square::~Square()
{
    //dtor
}

bool Square::isWalkable()
{
    switch (square) {
        
        case FLOOR:
        case DOOR_OPEN:
        case STAIRS_DOWN:
        case STAIRS_UP:
        	return true;
            break;
        default:
            break;
    }
    return false;
}

void Square::setType(squareType s)
{
    square = s;
    symbol = squareChar[s];
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
