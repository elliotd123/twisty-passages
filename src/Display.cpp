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
#include "Config.h"
#include "Display.h"

Display::Display()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

Display::~Display()
{
    endwin();
}

//Draw out a level, not including monsters, items, etc.
void Display::drawLevel(Level& level)
{
    for (int i = 0; i < level.levelSizeY; i++)
    {
        for (int j = 0; j < level.levelSizeX; j++)
        {
            if (level.squares[j][i].seen)
            {
            	move(i,j);
				char c = level.squares[j][i].getSymbol();
				printw("%c",c);
            }
        }
    }
    refresh();
}

//Draw all the Items that are on the floor of the level.
void Display::drawItems()
{
	//TODO: Need items first before we can draw them
}

void Display::drawCharStats(Character& character) {
	move(0,0);
	printw("HP: %i",character.hp);
	refresh();
}

//Draw all the monsters on the level
void Display::drawMonsters(Level& level, std::vector<Monster>& monsters)
{
	for (int i = 0; i < monsters.size(); i++)
	{
		move(monsters[i].location.y,monsters[i].location.x);
			printw("%c",monsters[i].symbol);
	}
	refresh();
}

//Draw a single monster on the level
void Display::drawMonster(Level& level, Monster& monster)
{
		move(monster.location.y,monster.location.x);
		printw("%c",monster.symbol);
		refresh();
}

//Simply grab the input from the player keyboard and return its integer equivalent
int Display::getInput()
{
    return getch();
}

//Output a single character at a location on the screen immediately
void Display::output(char c, int x, int y)
{
	move(y,x);
	printw("%c",c);
	refresh();
}

//Output an integer at a location on the screen immediately
//TODO: Handle numbers that go off the edge of the display
void Display::output(int i, int x, int y)
{
	move(y,x);
	printw("%i",i);
	refresh();
}

//Ouput a string starting at a location on the screen immediately
//TODO: Handle strings that go off the edge of the display
void Display::output(std::string& s, int x, int y)
{
	move(y,x);
	printw(s.c_str());
	refresh();
}


//Set an entire row to ' '
void Display::clearRow(int row)
{
	Config * c = c->getInstance();
	char blank = ' ';
	for (int i = 0; i < c->getInt("LEVEL_SIZE_X"); i++)
	{
		move(row,i);
		printw("%c",blank);
	}
	refresh();
}

void Display::clearScreen()
{
	clear();
}

//Move the cursor to the location
void Display::moveCursor(Coord location)
{
	move(location.y,location.x);
}
