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
#ifndef SQUARE_H
#define SQUARE_H

enum squareType { 
    WALL,
    HARD_WALL,
    FLOOR,
    DOOR_OPEN,
    DOOR_CLOSED,
    STAIRS_UP,
    STAIRS_DOWN 
};

const char squareChar[] = {
    //WALL
    '#',
    //HARD_WALL
    '#',
    //FLOOR
    '.',
    //DOOR_OPEN,
    '-',
    //DOOR_CLOSED,
    '+',
    //STAIRS_UP
    '<',
    //STAIRS_DOWN
    '>'
};

class Square
{
    public:
        squareType square;
        Square();
        virtual ~Square();

        bool isWalkable();
        void setType(squareType);
        int getType();
        char getSymbol();
        void setSymbol(char c);
        bool seen;
        bool isVisible;

    protected:
    private:
        bool walkable;
        char symbol;
};

#endif // SQUARE_H
