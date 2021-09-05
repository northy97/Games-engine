#pragma once
#include "Entity.h"
class bulletEntity :
	public Entity
{
public:
	bulletEntity(std::string spriteName);
	~bulletEntity();
	
	void update() override final;
	
};

