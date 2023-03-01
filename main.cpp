#include "sgg/graphics.h"
#include "GUI.h"

// Function that is continously running and drawing all our objects to the screen
void draw()
{
	GUI* gui{ GUI::Get() };
	gui->draw();
}

// Function that is continously running and updating all our objects to the screen
void update(float ms)
{
	GUI* gui{ GUI::Get() };
	gui->update();
}

// Creating Window, getting the instance of GUI, initializing objects, setting canvas sizes
void createProgram()
{
	graphics::createWindow(1400, 800, WindowConst::WINDOW_NAME);

	GUI* gui{ GUI::Get() };
	gui->init();

	//Defines the extents of the drawing canvas in the custom units used by the application.
	graphics::setCanvasSize(CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);


	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
}

int main()
{
	createProgram();
	graphics::startMessageLoop();
	graphics::destroyWindow();

	GUI::releaseInstance();

	return 0;
}