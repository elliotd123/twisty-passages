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
#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <ncurses.h>
#include <vector>

#include "Level.h"
#include "Monster.h"

class Display
{
    public:
        Display();
        virtual ~Display();

        void drawLevel(Level& level);
        void drawItems();
        void drawMonster(Level& level, Monster& monster);
        void drawMonsters(Level& level, std::vector<Monster>& monsters);

        void output(char c, int x, int y);
		void output(int i, int x, int y);
		void output(std::string& s, int x, int y);
		void clearRow(int row);
		void clearScreen();
		void moveCursor(Coord location);
        int getInput();
    protected:
    private:
};

#endif // DISPLAY_H
