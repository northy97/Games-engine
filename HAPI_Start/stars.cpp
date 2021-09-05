#include "stars.h"
#include <random>
#include <iostream>




stars::stars()
{
	
	x = rand() % 1000;
	y = rand() % 1000;
	z = rand() % 100;
	Cx = 400;
	Cy = 400;
	eyeDistance = 200;
	red = rand() % 155 + 200 ;
	green = rand() % 155 + 200;
	blue = rand() % 155 + 200;
	
	
}

void stars::renderStar(BYTE* screen)
{
	

	const HAPISPACE::HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	if (keyData.scanCode['A'])
	{
		x++;
	}
	if (keyData.scanCode['D'])
	{
		x--;
	}
	if (keyData.scanCode['R'])
	{
		x = rand() % 1000;
	}
	

	

	z-=0.3;

	Sx = ((eyeDistance*(x - Cx)) / (z + eyeDistance)) + Cx;
	Sy = ((eyeDistance*(y - Cy)) / (z + eyeDistance)) + Cy;// formula for star movement

	if (x > 800 || x <= 0) // boundary
	{
		x = rand() % 800;
		
	}
	if (y > 800 || y <= 0)
	{
		y = rand() % 800;
	}




	HAPI_TColour colour(red, green, blue, 255); // colour set 
	BYTE *pnter = screen + (Sx + Sy * 800) * 4;

	if (z <= 0)
	{

		z = rand() % 300;



	}


	if (pnter > screen + (800 * 800) * 4)
	{

	}
	else
	{
		*(HAPI_TColour*)pnter = colour;

	}





}


stars::~stars()
{
}
