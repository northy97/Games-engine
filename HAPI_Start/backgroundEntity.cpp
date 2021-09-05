#include "backgroundEntity.h"



backgroundEntity::backgroundEntity(std::string spriteName) :Entity(spriteName)
{
	position = { 0,0 };
	side = "neutral";
	if (spriteName == "boom")// setting default background and the explosion graphic default frame  
	{
		frameNumber = 1;
		alive = false;
	}

	else
	{
		frameNumber = 0;
	}

	
}


backgroundEntity::~backgroundEntity()
{
}

void backgroundEntity::update()
{
}
