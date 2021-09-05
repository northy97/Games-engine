#include "Graphics.h"
#include "sprite.h"


Graphics::Graphics()
{
	
}


Graphics::~Graphics()
{
	for (auto i : spriteMap)
	{
		delete i.second;
	}
}

bool Graphics::initialise(int screenHeight,int screenWidth)
{
	height = screenHeight;
	width = screenWidth;
	HAPI.Initialise(height, width);
	screenPointer = HAPI.GetScreenPointer();
	return true;
}

bool Graphics::createSprite(const std::string & fileName, const std::string& name)
{
	sprite *newSprite = new sprite; // creating the sprite and storing it
	if (!newSprite->load(fileName,height,width))
	{
		delete newSprite;
		return false;
	}

	spriteMap[name] = newSprite;

	return false;
}

void Graphics::clearScreenGreyScale(int colourValue )
{
	memset(screenPointer, colourValue, height*width*4);

};



void Graphics::clearScreenColour( int r, int g, int b, int a)
{
	HAPI_TColour colour(r, g, b, a);
	BYTE *pnter;
	for (int x = 0; x < width*height * 4; x += 4)
	{
		pnter = screenPointer + x;
		*(HAPI_TColour*)pnter = colour;

	}

	

};

void Graphics::render(const std::string& name, int X, int Y, int &frameNumber)
{
	spriteMap[name]->render(screenPointer,width,height,X,Y,frameNumber);

	

}


void Graphics::renderFast(const std::string& name, int X, int Y)
{
	spriteMap[name]->renderFast(screenPointer, width, height, X, Y);

};