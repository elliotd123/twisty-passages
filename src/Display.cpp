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

#include <string>

Display::Display()
{
    //initscr();
    //cbreak();
    //noecho();
    //keypad(stdscr, TRUE);
	l = l->getInstance();
	c = c->getInstance();
	SDL_Init(SDL_INIT_VIDEO);
	if (!TTF_Init()) {
		l->log(Logger::FILE, "Error initializing TTF");
	};
	Dimension window_res = Dimension();
	window_res.x = c->getInt("RESOLUTION_X");
	window_res.y = c->getInt("RESOLUTION_Y");
	window = SDL_CreateWindow("Twisty Passages",
							  0,0,
						      window_res.x,window_res.y,
							  SDL_WINDOW_RESIZABLE);

	std::string fontFile = c->getString("FONT");
	if (!(font = TTF_OpenFont(fontFile.c_str(),12))) {
		l->log(Logger::FILE,"Font load error!");
	};

	clearScreen();
}

Display::~Display()
{
    //endwin();
	l->log(Logger::FILE, "Quitting SDL");
	TTF_Quit();
	SDL_Quit();
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
				
				char c = level.squares[j][i].getSymbol();
				output(c,j,i);
            }
        }
    }
	//SDL_UpdateWindowSurface(window);
    //refresh();
}

//Draw all the Items that are on the floor of the level.
void Display::drawItems()
{
	//TODO: Need items first before we can draw them
}

void Display::drawCharStats(Character& character) {
	//move(41,0);
	//printw("HP: %i/%i",(int)character.hp,(int)character.maxHp);
	//refresh();
	std::string statsString = "HP: " + std::to_string((int)character.hp)
	                          + "/" + std::to_string((int)character.maxHp);
	output(statsString,0,41);
}

void Display::drawLevelNumber(int level) {
	//move(0,0);
	//printw("Level: %i",level);
	//refresh();
	std::string levelString = "Level: " + std::to_string(level + 1);
	output(levelString,0,0);
}

//Draw all the monsters on the level
void Display::drawMonsters(Level& level, std::vector<Monster>& monsters)
{
	for (int i = 0; i < monsters.size(); i++)
	{
		//move(monsters[i].location.y,monsters[i].location.x);
		//printw("%c",monsters[i].symbol);
	}
	//refresh();
}

//Draw a single monster on the level
void Display::drawMonster(Level& level, Monster& monster)
{
	int x = monster.location.x;
	int y = monster.location.y;
	char c = monster.symbol;
	output(c,x,y);
}



//Output a single character at a location on the screen immediately, unless explicitly told not to
void Display::output(char c, int x, int y, bool immediate)
{
	std::string ch = std::string(1,c);
	output(ch,x,y,immediate);
}

//Output an integer at a location on the screen immediately
//TODO: Handle numbers that go off the edge of the display
void Display::output(int i, int x, int y)
{
	//move(y,x);
	//printw("%i",i);
	//refresh();
}

//Ouput a string starting at a location on the screen immediately
//TODO: Handle strings that go off the edge of the display
void Display::output(std::string& s, int x, int y, bool immediate)
{
	x = x * 8;
	y = y * 12;
	SDL_Color text_color = {255,255,255};
	SDL_Surface * text_surface;
	text_surface = TTF_RenderText_Solid(font,s.c_str(),text_color);
	SDL_Surface * win_surface = SDL_GetWindowSurface(window);

	SDL_Rect * dest_rect = new SDL_Rect;
	dest_rect->h = 12;
	dest_rect->w = 8;
	dest_rect->x = x;
	dest_rect->y = y;

	SDL_BlitSurface(text_surface,NULL,win_surface,dest_rect);
	if (immediate) {
		SDL_UpdateWindowSurface(window);
	}

	SDL_FreeSurface(text_surface);
	delete(dest_rect);
}


//Set an entire row to ' '
void Display::clearRow(int row)
{
	Config * c = c->getInstance();
	char blank = ' ';
	for (int i = 0; i < c->getInt("LEVEL_SIZE_X"); i++)
	{
		//move(row,i);
		//printw("%c",blank);
	}
	//refresh();
}

void Display::clearScreen()
{
	//clear();
	SDL_Surface * surface = SDL_GetWindowSurface(window);
	SDL_Rect * rect = new SDL_Rect;
	SDL_GetWindowSize(window,&rect->w,&rect->h);
	rect->x = 0;
	rect->y = 0;
	SDL_FillRect(surface,rect,0);
	delete(rect);
}

void Display::redraw() {
	SDL_UpdateWindowSurface(window);
}
