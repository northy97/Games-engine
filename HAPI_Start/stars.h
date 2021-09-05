#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;

class stars
{
public:
	stars();
	~stars();
	void renderStar(BYTE* screen);

private:
	float x, y, z;
	int Sx, Sy,Cx,Cy,eyeDistance;
	float green, red, blue;
	

	

};

