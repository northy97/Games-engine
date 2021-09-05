#include "playerEntity.h"
#include <HAPI_lib.h>
#include "World.h"
#include <algorithm>
#include <vector>
using namespace HAPISPACE;


playerEntity::playerEntity(std::string spriteName) :Entity(spriteName)
{
	side = "player";
	speed = 1;
	enemySide = "enemy";
	position = { 350,700 };
	life = 10;
	fireRate = 1;
	
}


playerEntity::~playerEntity()
{

}

void playerEntity::update()
{
	
	if (life <= 0)
	{
		alive = false;
	}
	
	
	const HAPISPACE::HAPI_TControllerData &controllerData = HAPI.GetControllerData(0); //input management for keyboard and controller
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	
	if (controllerData.isAttached)
	{
	
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.x < 770)
		{
			position.x +=speed;
		}
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.x > -30)
		{
			position.x -= speed;
		}
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.y > 580)
		{
			position.y -= speed;
		}
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.y < 800)
		{
			position.y += speed;
		}
		
		if (controllerData.digitalButtons[HK_DIGITAL_A])// digitial
		{

			if (controllerShoot)
			{
				controllerShoot = false;
				WORLD.shoot(side, enemySide, fireRate, position.x, position.y);//shoot = true
				


			}


		}


		if (!controllerData.digitalButtons[HK_DIGITAL_A])
		{
			controllerShoot = true;

		}




	}





	if (keyData.scanCode['D'] && position.x < 770)
		position.x += speed;
	if (keyData.scanCode['A'] && position.x > -30)
		position.x -= speed;
	if (keyData.scanCode['S'] && position.y <735)
		position.y += speed;
	if (keyData.scanCode['W'] && position.y > 580)
		position.y -=speed;
	

	if (keyData.scanCode['Q'] )// digitial
	{
		
		if (shoot )
		{
			shoot = false;
			WORLD.shoot(side, enemySide,fireRate,position.x,position.y);//shoot = true

			
		}

		
	}
	
	
	if (!keyData.scanCode['Q'])
	{
		shoot = true;

	}


		
		
	
	
			
		
		
	
		

		

		
		
	
		
}


