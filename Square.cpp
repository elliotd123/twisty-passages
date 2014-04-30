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

//TODO: Add stairs
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
