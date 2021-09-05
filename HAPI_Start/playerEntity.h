#pragma once
#include "Entity.h"

class playerEntity: public Entity
{
public:
	playerEntity(std::string spriteName);
	~playerEntity();

	void update() override final;

	bool shoot;
	bool controllerShoot ;
};

