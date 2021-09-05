#include "Entity.h"
#include "Graphics.h"


Entity::Entity(std::string spriteName): spriteName(spriteName)
{

}


Entity::~Entity()
{
}

void Entity::render(Graphics & graphics)
{
	

	

	if (spriteName == "boom" )
	{
		
		if (HAPI.GetTime() - lastTimeUpdatedAnimation >= animationTime) // animation for the explosion flipping through the frames of the spritesheet
		{
			if (frameNumber >= 4)
			{
				frameNumber = 1;

			}
			else
			{
				frameNumber++;
				
			}
			lastTimeUpdatedAnimation = HAPI.GetTime();
			
		}
	
		
	}
	graphics.render(spriteName, (int)position.x - (frameNumber * 64), (int)position.y, (int)frameNumber);
	
	
	
}

void Entity::getPosition(Vector2 &newPos)
{
	newPos = position;
}



