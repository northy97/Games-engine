#include "bulletEntity.h"
#include <iostream>


bulletEntity::bulletEntity(std::string spriteName) :Entity(spriteName)
{

	alive = false;
	speed = 2;
}


bulletEntity::~bulletEntity()
{
	
}

void bulletEntity::update()
{
	if (life <= 0) // killing bullet when hits something
	{
		alive = false;
	}





	if (position.y < 0 || position.y >800)// killing bullet when goes out of bounds
	{
		life--;
	}

	if (side == "player") 
	{
		position.y -= speed;
	}

	else
	{
		
		position.y += speed;
	}
	

}




