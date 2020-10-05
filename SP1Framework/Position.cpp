#include "Position.h"

Position::Position()
{
	pos.X = 0;
	pos.Y = 0;
}

Position::~Position()
{
	
}

void Position::setX(int x)
{
	pos.X = x; 
}

void Position::setY(int y)
{
	pos.Y = y; 
}
void Position::setPos(COORD p)
{
	pos.X = p.X;
	pos.Y = p.Y;
}

COORD Position::returnPos()
{
	return pos;
}

