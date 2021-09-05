
#include"World.h"
#include "Graphics.h"

// make namespace for own classes

using namespace HAPISPACE;
#if defined (DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new (_NORMAL_BLOCK,__FILE__,__LINE__) // debug code to check for memory leaks
#endif




void HAPI_Main()
{
	HAPI.SetShowFPS(1);
	WORLD.Run();
	
	
	
	

	


}











