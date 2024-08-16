#include "application.h"



int main(int argc, char* args[])
{
	Application app;
	
	app.isGameRunning = app.graphic.initializeWindow();

	app.setup();

	while (app.isGameRunning)
	{
		app.processInput();
		app.update();
		app.render();
	}

	app.releaseResources();

	return 0;
}