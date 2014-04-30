/*
 * Twisty Passages - A simple rogue-like dungeon crawler
 * Copyright (C) 2014  Elliot Dronebarger
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
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cstdlib>
#include <ctime>

class Coord
{
	public:
		Coord();
		Coord(int inX, int inY);
		virtual ~Coord();

		int x;
		int y;

	protected:
	private:
};

class Dimension
{
public:
		Dimension();
		Dimension(int inX, int inY);
		virtual ~Dimension();

		int x;
		int y;

	protected:
	private:
};

class Random
{
	public:
		Random();
		virtual ~Random();
		int getInt(int min, int max);
};

#endif /* UTILITIES_H_ */
