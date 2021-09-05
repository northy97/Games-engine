#pragma once
#include <vector>

class Graphics;
class Entity;


class World
{
private:

	bool gameOn{ false };
	bool reset{ false };
	float lastTimeUpdatedAnimation{ 0 };
	float animationTime{ 2500 };//used for animation timing for explosion 
	int bulletAmount{ 200 };
	static World* worldInstance;
	World();
	Graphics *m_graphics{ nullptr };
	std::vector<Entity*>entityVector;
	bool loadLevel();
	void update();
	void collisionCheck(Entity *x);
	void loadEntitys();
	void mainMenu();
	bool bossTrig = false;
	void die(Entity *i);
public:
	static World &getInstance();
	void shoot(std::string side,std::string  enemySide, float & fireRate, int xPos,int yPos);
	~World();
	void Run();
	void updateLifeUi();
	
	


};

#define WORLD  World::getInstance()