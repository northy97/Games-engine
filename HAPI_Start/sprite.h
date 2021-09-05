#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;

class sprite
{
public:
	sprite();
	~sprite();
	bool load(const std::string & fileName, const int height, const int width);
	void render(BYTE *screenPointer ,int screenHeight , int screenWidth,int x, int y,int frameNumber);
	void renderFast(BYTE *screenPointer, int screenHeight, int screenWidth, int x, int y);
	int mFrameNumber;

private:
	int SpriteWidth;
	int SpriteHeight;
	int screenHeight;
	int screenWidth;
	
	void clipToScreen(const int &x, const int &y, int & topLeftX, int & topLeftY, int & bottomRightX, int & bottomRightY);
	bool completelyOnScreen(int x, int y);
	bool completelyOffScreen(int x, int y);
	

	BYTE* data{nullptr};


};
