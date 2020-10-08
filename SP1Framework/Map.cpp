#include "game.h"
#include "game.h"
#include "Framework\console.h"
#include "Map.h"




Map::Map()
{
	unsigned short W = 0;
	unsigned short P = 20;
	unsigned short D = 40;
	unsigned short T = 1;
	unsigned short data[80][25] =
	{
			W,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,
			W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,W,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,W,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,
			W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,
			W,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,W,
			W,P,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,P,W,
			W,P,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,P,W,
			W,P,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,P,W,
			W,P,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,P,W,
			W,P,P,P,P,P,P,P,W,P,P,P,W,P,P,P,W,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,W,P,P,P,W,P,P,P,W,P,P,P,P,P,P,P,W,
			W,W,W,W,W,W,W,P,W,W,W,P,W,P,W,W,W,P,W,W,W,W,W,W,W,
			W,W,W,W,W,W,W,P,W,W,W,P,W,P,W,W,W,P,W,W,W,W,W,W,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,
			W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,P,W,P,W,
			W,P,W,P,W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,P,W,P,W,
			W,P,W,P,W,P,P,P,W,P,P,P,P,P,P,P,W,P,P,P,W,P,W,P,W,
			W,P,W,P,W,P,P,P,W,P,P,P,P,P,P,P,W,P,P,P,W,P,W,P,W,
			W,P,P,P,W,W,W,P,P,P,W,W,W,W,W,P,P,P,W,W,W,P,P,P,W,
			W,P,P,P,W,W,W,P,P,P,W,W,W,W,W,P,P,P,W,W,W,P,P,P,W,
			W,P,W,P,P,P,P,P,W,P,W,P,P,P,W,P,W,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,W,P,W,P,P,P,W,P,W,P,P,P,P,P,W,P,W,
			W,P,W,W,W,W,W,W,W,P,D,P,P,P,W,P,W,W,W,W,W,W,W,P,W,
			W,P,W,W,W,W,W,W,W,P,D,P,P,P,W,P,W,W,W,W,W,W,W,P,W,
			W,P,W,P,P,P,P,P,W,P,W,P,P,P,W,P,W,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,W,P,W,P,P,P,W,P,W,P,P,P,P,P,W,P,W,
			W,P,P,P,W,W,W,P,P,P,W,W,W,W,W,P,P,P,W,W,W,P,P,P,W,
			W,P,P,P,W,W,W,P,P,P,W,W,W,W,W,P,P,P,W,W,W,P,P,P,W,
			W,P,W,P,W,P,P,P,W,P,P,P,P,P,P,P,W,P,P,P,W,P,W,P,W,
			W,P,W,P,W,P,P,P,W,P,P,P,P,P,P,P,W,P,P,P,W,P,W,P,W,
			W,P,W,P,W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,P,W,P,W,
			W,P,W,P,W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,
			W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,W,W,W,W,W,W,P,W,W,W,P,W,P,W,W,W,P,W,W,W,W,W,W,W,
			W,W,W,W,W,W,W,P,W,W,W,P,W,P,W,W,W,P,W,W,W,W,W,W,W,
			W,P,P,P,P,P,P,P,W,P,P,P,W,P,P,P,W,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,W,P,P,P,W,P,P,P,W,P,P,P,P,P,P,P,W,
			W,P,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,P,W,
			W,P,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,P,W,
			W,P,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,W,P,W,W,W,W,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,P,W,
			W,P,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,P,W,
			W,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,P,P,P,W,P,W,
			W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,
			W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,W,W,W,W,W,W,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,W,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,P,P,P,P,P,P,P,P,P,W,P,P,P,P,P,P,P,P,P,W,P,W,
			W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,
			W,P,W,W,W,W,W,W,P,W,W,W,W,W,W,W,P,W,W,W,W,W,W,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,W,
			W,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,W,

	};

	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			mapArray[i][j] = data[i][j];


		}
	}


}
