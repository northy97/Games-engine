#include "World.h"
#include "Graphics.h"
#include "enemyEntity.h"
#include "backgroundEntity.h"
#include "playerEntity.h"
#include "bulletEntity.h"
#include <iostream>
#include <string>

World::World()
{
}

World *World::worldInstance{ nullptr };


World & World::getInstance()
{
	if (worldInstance == nullptr)
		worldInstance = new World;
	return *worldInstance;
}

World::~World()
{
	delete m_graphics;
	for (auto x : entityVector)
		delete x;
}

bool World::loadLevel()
{
	
	//load sprites 
	m_graphics ->createSprite("data\\playerSprite.tga", "player");
	m_graphics->createSprite("data\\enemy.png", "enemy");
	m_graphics->createSprite("data\\enemyBoss.png", "enemyBoss");
	m_graphics ->createSprite("data\\backgroundSpace.png","background");
	m_graphics->createSprite("data\\boom.png", "boom");
	
	for (int x = 0; x <= bulletAmount; x++)
	{
		m_graphics->createSprite("data\\spaceInvadersShot.png", "bullet");
	}
	
	for (int x = 0; x <=  10;x++)
	{
		m_graphics->createSprite("data\\heartpixelart.png", "heart");
	}
	
	loadEntitys(); 

	
	

	
	return true;
}

void World::update()
{



	while (HAPI.Update())
	{
		if (gameOn)
		{
			
			

			m_graphics->clearScreenGreyScale(0);

			for (auto x : entityVector)
			{

				x->update();
				die(x);

			}



			for (auto x : entityVector)// go here put loop in for conditioning move this off into function for if hit lopop through all entity
			{
				if (x->spriteName == "bullet" && x->alive)
				{
					for (auto i : entityVector)
					{

						if (i->spriteName != "bullet")
						{//x is bullet

							if (x->enemySide == i->side)
							{

								collisionCheck(x);
							}

						}
					}

				}


			}

			bool isEnemy = false;
			for (auto x : entityVector)
			{

				if (x->position.y > 800 && x->spriteName != "bullet")
				{
					gameOn = false;
				}


				if (x->alive)
				{

					x->render(*m_graphics);
					if (x->spriteName == "enemy" )
					{
						isEnemy = true;
					}

					
				}
				
			
			}



			if (isEnemy == false )
			{
		
				for (auto x : entityVector)
				{

					if (bossTrig == true && x->spriteName == "enemyBoss")
					{
						if (x->alive == false)
						{

							gameOn = false;
						}
					}

					if (x->spriteName == "enemyBoss" && x->alive == false)// trigger once spawn boss
					{
						x->alive = true;
						x->position = { 0,0 };
						bossTrig = true;
					}

					

					
				}

			
				
			}
			




			if (HAPI.GetTime() - lastTimeUpdatedAnimation >= animationTime)
			{
				entityVector[2]->alive = false;// put annimation stop here after set amount of frames
				lastTimeUpdatedAnimation = HAPI.GetTime();
			}

			if (entityVector[1]->life <= 0)//player dead 
			{

				gameOn = false;


				


			}
			HAPI.RenderText(0, 10, HAPI_TColour(255, 255, 0), "player life :  " + std::to_string(entityVector[1]->life), 25);
			updateLifeUi();

		}

		if(!gameOn )
		{
			loadEntitys();
			mainMenu();
		}
	}
	
}

void World::collisionCheck(Entity *x)
{
	int hitBoxMulti = 1 ;
	
	for (auto i : entityVector)
	{
		if (i->spriteName == "enemyBoss")
		{
			hitBoxMulti = 2;
		}
		else
		{
			hitBoxMulti = 1;
		}

		//x is bullet 
		//i is enemy 

		if (i->side == "player" || i->side == "enemy")
		{
			
			if (x->enemySide == i->side && i->spriteName != "bullet")
			{
				
				if (x->spriteName == "bullet" && x->alive)
				{

					if (x->position.x > i->position.x && i->alive)
					{
						if (x->position.x < i->position.x +( 86 * hitBoxMulti))
						{

							if (x->position.y > i->position.y)
							{
								if (x->position.y < i->position.y + 65)
								{
									//
									i->life--;
									x->life --;
									

									


								}

							}

						}

					}

				}
			}
			}
			
		
	}
	
}

void World::loadEntitys()
{
	
	entityVector.clear();
	playerEntity *newPlayer = new playerEntity("player");
	backgroundEntity *newBackground = new backgroundEntity("background");
	backgroundEntity *boom = new backgroundEntity("boom");

	enemyEntity *enemyBoss = new enemyEntity("enemyBoss");

	entityVector.push_back(newBackground);
	entityVector.push_back(newPlayer);
	entityVector.push_back(boom);

	entityVector.push_back(enemyBoss);
	
	bossTrig = false;
	
	//index 2 is explosion


	for (int x = 0; x < 12; x++)
	{
		enemyEntity *newEnemy = new enemyEntity("enemy");
		entityVector.push_back(newEnemy);
		newEnemy->position = { 200 * (float)x/2,100 };
		if (x > 5)
		{
			newEnemy->position = { 200 * ((float)x -6) / 2,200 };
		}
	}
	

	for (int x = 0; x <= bulletAmount; x++)
	{

		bulletEntity *bullet = new bulletEntity("bullet");
		entityVector.push_back(bullet);
	}

	for (int x = 0; x < entityVector[1]->life; x++)
	{
		backgroundEntity *heart = new backgroundEntity("heart");
		entityVector.push_back(heart);
		heart->position = { 50* (float)x / 2,40 };
	}
}

void World::mainMenu()
{
	m_graphics->clearScreenGreyScale(0);
	HAPI.RenderText(80, 10, HAPI_TColour(255, 0, 0), "space Invaders  ", 50);
	HAPI.RenderText(80, 60, HAPI_TColour(255, 0, 0), "start game press r  ", 50);
	HAPI.RenderText(80, 120, HAPI_TColour(255, 0, 0), "press Y on controller ", 50);
	HAPI.RenderText(80, 180, HAPI_TColour(255, 0, 0), "keyboard press q to shoot wsad to move ", 35);
	HAPI.RenderText(80, 240, HAPI_TColour(255, 0, 0), "controller left analog move a to shoot ", 35);
	
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPISPACE::HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	if (keyData.scanCode['R'] || controllerData.digitalButtons[HK_DIGITAL_Y])
	{
		loadEntitys();
		gameOn = true;
	
	}
}

void World::shoot(std::string side,std::string  enemySide,float &fireRate, int xPos, int yPos)
{
	int min = 1000;
	int max = 2500;
	
	fireRate = min + (rand() % static_cast<int>(max - min + 1));
	for (auto x : entityVector)
	{
	
		if (!x->alive && x->spriteName == "bullet")
		{

			x->alive = true;
			x->life = 1;// finish in the player entity
			x->position.x = xPos +20;
			x->position.y = yPos;
			x->side = side;
			x->enemySide = enemySide;

			
			break;
			
			
			
		}


	}
		

	
}

void World::Run()
{
	m_graphics = new Graphics;
	if (!m_graphics->initialise(800, 800))
	{
		return;
	}
	if (loadLevel())
	{

		update();
	}
}

void World::die(Entity *i)
{
	
		auto explosion = entityVector[2]; // update explosion 


		if (i->spriteName != "bullet" && i->spriteName != "boom")
		{
			
			if (i->alive == false && i->deadTrig == false)
			{
				
				explosion->position = {i->position.x,i->position.y };
			
				explosion->alive = true;
				
				i->deadTrig = true;
				
			}
			
		}
	
	
}

void World::updateLifeUi()
{
	int playerLife = entityVector[1]->life;
	bool lifeRemove = true;
	int heartCount = 0;

	for (auto x : entityVector)
	{
		if (x->spriteName == "heart" )
		{
			heartCount++;
			if (heartCount -1 == playerLife)
			{
				x->alive = false;
			}

			
		}
	}
}
