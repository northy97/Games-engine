#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <unordered_map>


class sprite;

class Graphics
{

public:
	Graphics();
	~Graphics();

	bool initialise(int screenHeight, int screenWidth);
	bool createSprite(const std::string& fileName,const std::string& name);
	void clearScreenColour( int r, int g, int b, int a);
	void clearScreenGreyScale( int colourValue);
	void render(const std::string& ,int posX, int posY,int& frameNumber);
	void renderFast(const std::string&, int posX, int posY);

	
private:
	
	int height;
	int width;
	BYTE * screenPointer{ nullptr };

	std::unordered_map<std::string, sprite*>spriteMap;
	
	
	
	
};

