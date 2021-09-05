#pragma once
#include "Entity.h"

class enemyEntity :public Entity
{
public:
	enemyEntity(std::string spriteName);
	~enemyEntity();
	void update() override final;


private:
	float lastTimeUpdatedAnimation{ 0 };// animation timing for firing
	bool moveLeft = false;// bool trigger for direction change
	
	


	


};

