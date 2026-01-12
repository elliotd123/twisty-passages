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
#include <cassert>
#include <cmath>
#include <iostream>

#include "Config.h"
#include "Level.h"

Level::Level()
{
	c = c->getInstance();
	mons_data = mons_data->getInstance();
    levelSizeX = c->getInt("LEVEL_SIZE_X");
    levelSizeY = c->getInt("LEVEL_SIZE_Y");

	//Initialize all squares with default constructor (As walls)
	for (int i = 0; i < levelSizeX; i++) {
		squares.push_back(std::vector<Square>());
		for (int j = 0; j < levelSizeY; j++) {
			squares[i].push_back(Square());
		}
	}

    static Random rand = Random();

    int rand_int = rand.getInt(c->getInt("MIN_ROOMS"),c->getInt("MAX_ROOMS"));
    for (int i = 0; i < rand_int; i++)
    {
    	addRoom();
    }
    makeHalls();
    addStairs();
}

Level::~Level()
{
    //dtor
}

void Level::addRoom()
{
	int centerX, centerY, locX, locY, sizeX, sizeY;
	bool invalidRoom;
	Coord location,center;
	Dimension size;
	int attempts = 0;
	do
	{
		invalidRoom = false;

		//Create random room size
		int min_room_size = c->getInt("MIN_ROOM_SIZE");
		int max_room_size = c->getInt("MAX_ROOM_SIZE");
		sizeX = (rand() % (max_room_size - min_room_size) + min_room_size);
		sizeY = (rand() % (max_room_size - min_room_size) + min_room_size);
		size = Dimension(sizeX,sizeY);

		//Create random room location
		locX = (rand() % (levelSizeX - sizeX)+1);
		locY = (rand() % (levelSizeY - sizeY)+1);
		location = Coord(locX,locY);

		//Pick a square in the room to be the "Center" of the room. May be anywhere in the room
		centerX = (rand() % sizeX) + locX;
		centerY = (rand() % sizeY) + locY;
		center = Coord(centerX,centerY);

		//Check to see if the room is on the edge of the map
		if ((location.x + size.x + 2) >= levelSizeX
		    || (location.x - size.x - 2) <= 0)
		{
			invalidRoom = true;
		}

		if ((location.y + size.y + 2) >= levelSizeY
		    || (location.y - size.y - 2) <= 0)
		{
			invalidRoom = true;
		}

		//Make sure a room isn't smashed into another room
		for (int i = location.x-1; i < (location.x+size.x+1); i++)
		{
			for (int j = location.y-1; j < (location.y+size.y+1); j++)
			{
				if (i > c->getInt("LEVEL_SIZE_X") - 1
				    || j > c->getInt("LEVEL_SIZE_Y") - 1) {
						invalidRoom = true;
					} else {
						if (squares[i][j].getType() == FLOOR) invalidRoom = true;
					}
			}
		}

		attempts += 1;
		if (attempts > 50) {
			//TODO: Log entry here
			//Couldn't find a place to put the room. We gotta stop here.
			return;
		}

	} while (invalidRoom);

	//When we've found a valid place and size to put a room, add it.
	rooms.push_back(Room(center,size,location));

	//Convert squares that are in the new room into floor squares
	for (int i = location.x; i < (location.x+size.x); i++)
	{
		for (int j = location.y; j < (location.y+size.y); j++)
		{
			squares[i][j].setType(FLOOR);
		}
	}
	//Testing where the room centers are
	/*
	for (int i = 0; i < rooms.size(); i++)
	{
		squares[rooms[i].centerX][rooms[i].centerY].setType(DOOR_CLOSED);
	}
	*/
}


/*
 * We make halls by starting from one room center and proceeding toward the next room's center.
 * If both x and y locations are off, randomly choose which one to follow next
 * Otherwise, proceed in a straight line until the hall location matches the destination
 *
 * TODO: Convert locations into Coord() instead of explicit integers
 */
void Level::makeHalls()
{
	for (unsigned int i = 1; i < rooms.size(); i++)
	{
		int startX = rooms[i-1].center.x;
		int startY = rooms[i-1].center.y;

		int curX = startX;
		int curY = startY;

		int endX = rooms[i].center.x;
		int endY = rooms[i].center.y;

		while ((curX != endX) || (curY != endY))
		{
			if ((curX != endX) && (curY != endY))
			{
				int rand_num = rand() % 2;
				if (rand_num == 0)
				{
					if (curX > endX) curX--;
					else curX++;
				}
				else
				{
					if (curY > endY) curY--;
					else curY++;
				}
			}
			else if (curX != endX)
			{
				if (curX > endX) curX--;
				else curX++;
			}
			else
			{
				if (curY > endY) curY--;
				else curY++;
			}

			squares[curX][curY].setType(FLOOR);
		}
	}
}

/*
 * Add a monster to a random location in the level
 * TODO: Make sure we're not stacking monsters on top of other monsters or on the character.
 * Bad things could happen if that were the case.
 */
void Level::addMonster(Monster& monster)
{
	bool validSpot=false;
	while (!validSpot)
	{
		int x = rand() % levelSizeX;
		int y = rand() % levelSizeY;

		if (squares[x][y].isWalkable())
		{
			monster.location.x = x;
			monster.location.y = y;
			validSpot=true;
		}
	}
	monsters.push_back(monster);
}

void Level::addMonsters(int level) {
	int minMonsters = c->get<int>("MIN_MONSTERS_SPAWN");
	int maxMonsters = c->get<int>("MAX_MONSTERS_SPAWN");
	Random r = Random();
	for (int i = 0; i < r.getInt(minMonsters,maxMonsters); i++) {
		Monster m = mons_data->getRandomMonster(level);
		addMonster(m);
	}
}

void Level::addStairs()
{
	squares[rooms[0].center.x][rooms[0].center.y].setType(STAIRS_UP);
	squares[rooms[rooms.size()-1].center.x][rooms[rooms.size()-1].center.y].setType(STAIRS_DOWN);
}

Monster * Level::monsterAt(const Coord& coordinate) {
	for (unsigned int i = 0; i < monsters.size(); i++)
	{
		if (coordinate.x == monsters[i].location.x && coordinate.y == monsters[i].location.y)
		{
			return &monsters[i];
		}
	}
	return NULL;
}


bool Level::isAllWalls(const Coord& location)
{
	for (int i = location.x-1; i <= location.x+1; i++)
	{
		for (int j = location.y-1; j <= location.y+1; j++)
		{
			if (squares[i][j].getType() != WALL)
				return false;
		}
	}
	return true;
}

bool Level::isLOS(const Coord& target, const Monster& source) {
	Coord sourceLoc = source.location;
	if (distance(sourceLoc,target) > source.visibility) {
		return false;
	}
	for (double ang = 0.0; ang < 360.0; ang += c->getDouble("VISIBILITY_ANGLE_INCREMENT")) {
		bool hitWall = false;
		for (double i = 0.0; i <= source.visibility; i+= c->getDouble("VISIBILITY_LINEAR_INCREMENT")) {
			if (hitWall) {
				break;
			}
			double ang_rad = ang * (3.14 / 180.0);
			double x_doub = cos(ang_rad) * i;
			int x = (int) x_doub;
			double y_doub = sin(ang_rad) * i;
			int y = (int) y_doub;
			x += sourceLoc.x;
			y += sourceLoc.y;

			if (x == target.x && y == target.y) {
				return true;
			}
		}
	}
	return false;
}

void Level::updateVisible(const Character& player)
{
	Coord playerLocation = player.location;
	for (int i = 0; i < levelSizeX; i++)
	{
		for (int j = 0; j < levelSizeY; j++)
		{
			squares[i][j].isVisible = false;
		}
	}

	for (double ang = 0.0; ang < 360.0; ang += c->getDouble("VISIBILITY_ANGLE_INCREMENT")) {
		bool hitWall = false;
		for (double i = 0.0; i <= player.visibility; i+= c->getDouble("VISIBILITY_LINEAR_INCREMENT")) {
			if (hitWall) {
				break;
			}
			double ang_rad = ang * (3.14 / 180.0);
			double x_doub = cos(ang_rad) * i;
			int x = (int) x_doub;
			double y_doub = sin(ang_rad) * i;
			int y = (int) y_doub;
			x += playerLocation.x;
			y += playerLocation.y;

			squares[x][y].seen = true;
			squares[x][y].isVisible = true;

			switch (squares[x][y].getType()) {
				case WALL:
				case HARD_WALL:
				case DOOR_CLOSED:
					hitWall = true;
					break;
				default:
					break;
			}
		}
	}
}

bool Level::isAdjacent(const Monster & mons1, const Monster &mons2) {
	Coord loc1 = mons1.location;
	Coord loc2 = mons2.location;

	if (abs(loc1.x - loc2.x) <= 1
	&&  abs(loc1.y - loc2.y) <= 1) {
		return true;
	}
	return false;
}