#include "enemyEntity.h"
#include "World.h"


enemyEntity::enemyEntity(std::string spriteName) :Entity(spriteName)
{
	side = "enemy";
	enemySide = "player";
	if (spriteName == "enemyBoss")// conditioning  to set default state of entity depending on enemy type
	{
		life = 200;
		
		alive = false;
		position = { -100,-100 };
	}
	else
	{
		life = 5;
	}
	
	speed = 0.5;
}


enemyEntity::~enemyEntity()
{
}

void enemyEntity::update()
{
	
	
	if (spriteName == "enemyBoss" && alive)// conditioning  to set default state of entity depending on enemy type
	{
		fireRate = 300;
	
		if (!moveLeft)
		{
			position.x += speed;
			position.y += 0.05;
			if (position.x > 700)
			{
				moveLeft = true;
				
			}
		}

		else
		{
			position.x -= speed;
			position.y += 0.05;
			if (position.x <0)
			{
				moveLeft = false;
				
			}
		}

	}
	else
	{
	if (!moveLeft)
	{
		position.x +=speed;
		if (position.x > 800)
		{
			moveLeft = true;
			position.y += 100;
		}
	}

	else
	{
		position.x -=speed;
		if (position.x < -100)
		{
			moveLeft = false;
			position.y += 100;
		}
	}
	}
	
	
	
	
	if (HAPI.GetTime() - lastTimeUpdatedAnimation >= fireRate && alive)// timing for the fire rate 
	{
		
		WORLD.shoot(side, enemySide, fireRate ,position.x, position.y); // offset to match better
		if (spriteName == "enemyBoss")
		{
			WORLD.shoot(side, enemySide, fireRate, position.x + 145, position.y);
		}
		
		lastTimeUpdatedAnimation = HAPI.GetTime();
	}

	
	if (life <= 0)
	{
		
		alive = false;
	}

	
}


