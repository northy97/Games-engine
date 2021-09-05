#pragma once
#include <string>
#include <HAPI_lib.h>


struct Vector2
{
	float x;
	float y;
};


class Graphics;

class Entity
{

	
public:
	float fireRate{ 800 };
	int frameNumber{ 0 };
	bool alive{ true };
	float speed{ 2.0f };
	int life = 1;
	bool deadTrig = false;


	Vector2 position;
	std::string spriteName;
	Entity(std::string spriteName);
	virtual ~Entity();
	void render(Graphics &graphics);
	void setPosition(Vector2 newPos) { position = newPos; }
	void getPosition(Vector2 &newPos);
	std::string side;
	std::string enemySide;
	virtual void update() = 0;
	
	float lastTimeUpdatedAnimation{ 0 };
	float animationTime{ 100 };


};

