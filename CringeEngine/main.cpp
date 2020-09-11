#include "AppWindow.h"

int main() 
{
	AppWindow app;

	if (app.init()) 
	{
		while (app.isRunning())
		{
			app.broadcast(); //Sends and translates window messages
		}
	}

	return 0;
}