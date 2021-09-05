#include "sprite.h"
#include <algorithm>
#include <HAPI_lib.h>
#include <vector>
using namespace HAPISPACE;


sprite::sprite()
{
}


sprite::~sprite()
{
	delete[]data;
}

bool sprite::load(const std::string & fileName,const int height,const int width)
{
	screenWidth = width;
	screenHeight = height;

	if (!HAPI.LoadTexture(fileName, &data, SpriteWidth, SpriteHeight))
		return false;

	return true;
}

void sprite::render(BYTE *screenPointer, int screenHeight, int screenWidth, int x, int y,int frameNumber)
{
	mFrameNumber = frameNumber;
	if (!completelyOffScreen(x,y))
	{

		
		int topLeftX{ 0 };// adjust these values with the frame number to get parts of image
		int topLeftY{ 0 };
		int bottomRightX{ SpriteWidth };
		int bottomRightY{ SpriteHeight };


		if (mFrameNumber != 0)
		{
			int oneFrame = SpriteWidth / 4;
			std::cout << mFrameNumber << std::endl;
			topLeftX = 0 + (oneFrame*(mFrameNumber));// choosing positions for the part of the spritesheet to render
			topLeftY = 0;
			bottomRightX = oneFrame + (oneFrame*(mFrameNumber));
			bottomRightY = oneFrame;

		}
		

		


		

		char *tempPtr{ (char*)(screenPointer + (x + y * screenWidth) * 4) };
		char *dataPtr{ (char*)data };



		if (!completelyOnScreen(x,y))
		{
			clipToScreen(x, y, topLeftX, topLeftY, bottomRightX, bottomRightY);
		}

		for (int y = topLeftY; y < bottomRightY; y++)
		{

			HAPISPACE::HAPI_TColour *linePtr{ (HAPISPACE::HAPI_TColour*)(tempPtr + (topLeftX + y * screenWidth) * 4) };
			HAPISPACE::HAPI_TColour *dLinePtr{ (HAPISPACE::HAPI_TColour*)(dataPtr + (topLeftX + y * SpriteWidth) * 4) };

			for (int x = topLeftX; x < bottomRightX; x++)
			{


				BYTE alpha = dLinePtr->alpha;

				if (alpha == 255)
				{
					memcpy(linePtr, dLinePtr, 4);
				}

				else if (alpha > 0)
				{
					BYTE red = dLinePtr->red;
					BYTE green = dLinePtr->green;
					BYTE blue = dLinePtr->blue;

					float mod = (float)alpha / 255.0f;
					linePtr->red = linePtr->red + ((alpha *(red - linePtr->red)) >> 8);
					linePtr->green = linePtr->green + ((alpha *(green - linePtr->green)) >> 8);
					linePtr->blue = linePtr->blue + ((alpha *(blue - linePtr->blue)) >> 8);

				}

				dLinePtr++;
				linePtr++;

			}


		}
	}
}

void sprite::renderFast(BYTE *screenPointer, int screenHeight, int screenWidth, int x, int y)
{
	if (!completelyOffScreen(x, y))
	{
		int topLeftX{ 0 };
		int topLeftY{ 0 };
		int bottomRightX{ SpriteWidth };
		int bottomRightY{ SpriteHeight };

		char *tempPtr{ (char*)(screenPointer + (x + y * screenWidth) * 4) };
		char *dataPtr{ (char*)data };

		if (!completelyOnScreen(x, y))
		{
			clipToScreen(x, y, topLeftX, topLeftY, bottomRightX, bottomRightY);
		}

		for (int y = topLeftY; y < bottomRightY; y++)
		{

			HAPISPACE::HAPI_TColour *linePtr{ (HAPISPACE::HAPI_TColour*)(tempPtr + (topLeftX + y * screenWidth) * 4) };
			HAPISPACE::HAPI_TColour *dLinePtr{ (HAPISPACE::HAPI_TColour*)(dataPtr + (topLeftX + y * SpriteWidth) * 4) };

			for (int x = topLeftX; x < bottomRightX; x++)
			{

				memcpy(linePtr, dLinePtr, 4);
				linePtr++;
				dLinePtr++;
			}

		}
	}

}

void sprite::clipToScreen(const int & x, const int & y, int & topLeftX, int & topLeftY, int & bottomRightX, int & bottomRightY)
{


	

	


	bottomRightX = std::min(bottomRightX, screenWidth - x);
	bottomRightY = std::min(bottomRightY, screenHeight - y);

	topLeftX = std::max(0, -x);
	topLeftY = std::max(0,- y);

	if (mFrameNumber != 0)
	{
		int oneFrame = SpriteWidth / 4;
		std::cout << mFrameNumber << std::endl;
		topLeftX = 0 + (oneFrame*(mFrameNumber));// choosing positions for the part of the spritesheet to render
		topLeftY = 0;
		bottomRightX = oneFrame + (oneFrame*(mFrameNumber));
		bottomRightY = oneFrame;

	}




	


}

bool sprite::completelyOnScreen(int x, int y)
{// do for onscreen
	if (x <0 || x + SpriteWidth > screenWidth)
	{
		return false;
	}

	if (y < 0 || y + SpriteHeight > screenHeight)
	{
		return false;
	}

	
	return true;

}

bool sprite::completelyOffScreen(int x, int y)
{

	if (x < 0)
	{
		if (x + SpriteWidth < 0 )
		{
			return true;
		}
	}

	else if  (x > screenWidth)
	{
		if (x + SpriteWidth > screenWidth)
		{
			return true;
		}
	}

	else if (y < 0)
	{
		if (y + SpriteHeight < 0)
		{
			return true;
		}
	}

	else if (y > screenHeight)
	{
		if (y + SpriteHeight > screenHeight)
		{
			return true;
		}
	}

	
	
	return false;

}



