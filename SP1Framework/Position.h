#pragma once
#include "Framework/console.h"

class Position 
{
private:
	COORD pos;
public:
	Position();
	~Position();
	void setX(int x);
	void setY(int y);
	void setPos(COORD position);
	COORD returnPos();
	int getX();
	int getY();
};

