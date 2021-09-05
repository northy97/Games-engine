#pragma once
#include "Entity.h"
class backgroundEntity :public Entity
{
public:
	backgroundEntity(std::string spriteName);
	~backgroundEntity();
	void update()  override final;
	
};

