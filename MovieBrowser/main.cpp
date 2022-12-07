#include "sgg/graphics.h"
#include "constants.h"
#include "GUI.h"

void draw()		
{
	GUI* gui{ GUI::Get() };
	gui->draw();

}

void update(float ms)
{
	GUI* gui{ GUI::Get() };
	gui->update();

}

int main()
{
	graphics::createWindow(1400, 800, WindowConst::WINDOW_NAME);		//Creates the window
	
	GUI* gui{ GUI::Get() };
	gui->init();

	graphics::setCanvasSize(CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT);		 //Defines the extents of the drawing canvas in the custom units used by the application.
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);


	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::startMessageLoop();	//Starting the loop of our program. This function, processes all window and user events. Its also responsible for calling the draw to refresh the visual content, and update to update our screen
	
	GUI::releaseInstance();		//Delete the GUI
	return 0;
}


/*
	- Start message loop :	Starting the loop of our program. This function, processes all window and user events. Its also responsible for calling the draw to refresh the visual content, and update to update our screen

	- Draw : called when we want to draw something 

*/