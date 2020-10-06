#pragma once
#include "Position.h"

class Entity
{

private:
	Position position;
	bool alive;

public:
	~Entity();
	Entity(bool alive);
	
	

};

