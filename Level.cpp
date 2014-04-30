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
#include "Level.h"

Level::Level()
{
    levelSizeX = LEVEL_SIZE_X;
    levelSizeY = LEVEL_SIZE_Y;

    //Initialize all squares with default constructor (As walls)
    for (int i = 0; i < levelSizeY; i++)
    {
        for (int j = 0; j < levelSizeX; j++)
        {
            squares[j][i] = Square();
        }
    }
    static Random rand = Random();

    int rand_int = rand.getInt(MIN_ROOMS,MAX_ROOMS);
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
	do
	{
		invalidRoom = false;

		//Create random room size
		sizeX = (rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE);
		sizeY = (rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE);
		size = Dimension(sizeX,sizeY);

		//Create random room location
		locX = (rand() % (LEVEL_SIZE_X - sizeX)+1);
		locY = (rand() % (LEVEL_SIZE_Y - sizeY)+1);
		location = Coord(locX,locY);

		//Pick a square in the room to be the "Center" of the room. May be anywhere in the room
		centerX = (rand() % sizeX) + locX;
		centerY = (rand() % sizeY) + locY;
		center = Coord(centerX,centerY);

		//Check to see if the room is on the edge of the map
		if ((location.x + size.x + 2) >= levelSizeX)
		{
			invalidRoom = true;
		}

		if ((location.y + size.y + 2) >= levelSizeY)
		{
			invalidRoom = true;
		}

		//Make sure a room isn't smashed into another room
		for (int i = location.x-1; i < (location.x+size.x+1); i++)
		{
			for (int j = location.y-1; j < (location.y+size.y+1); j++)
			{
				if (squares[i][j].getType() == FLOOR) invalidRoom = true;
			}
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
void Level::addMonster(Monster* monster)
{
	bool validSpot=false;
	while (!validSpot)
	{
		int x = rand() % LEVEL_SIZE_X;
		int y = rand() % LEVEL_SIZE_Y;

		if (squares[x][y].isWalkable())
		{
			monster->location.x = x;
			monster->location.y = y;
			validSpot=true;
		}
	}
}

void Level::addStairs()
{
	squares[rooms[0].center.x][rooms[0].center.y].setType(STAIRS_UP);
	squares[rooms[rooms.size()-1].center.x][rooms[rooms.size()-1].center.y].setType(STAIRS_DOWN);
}

bool Level::isMonster(Coord coordinate)
{
	for (unsigned int i = 0; i < monsters.size(); i++)
	{
		if (coordinate.x == monsters[i].location.x && coordinate.y == monsters[i].location.y)
		{
			return true;
		}
	}
	return false;
}


bool Level::isAllWalls(Coord location)
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

void Level::updateVisible(Coord playerLocation)
{
	for (int i = 0; i < LEVEL_SIZE_X; i++)
	{
		for (int j = 0; j < LEVEL_SIZE_Y; j++)
		{
			if (i > 0 && j > 0)
				if (i < LEVEL_SIZE_X && j < LEVEL_SIZE_Y)
					squares[i][j].isVisible = false;
		}
	}

	for (int i = (playerLocation.x-5); i <= (playerLocation.x+5); i++)
	{
		for (int j = (playerLocation.y-5); j <= (playerLocation.y+5); j++)
		{
			if (i > 0 && j > 0)
			{
				if (i < LEVEL_SIZE_X && j < LEVEL_SIZE_Y)
				{
					if (!isAllWalls(Coord(i,j)))
					{
						squares[i][j].seen = true;
						squares[i][j].isVisible = true;
					}
				}
			}
		}
	}
}
