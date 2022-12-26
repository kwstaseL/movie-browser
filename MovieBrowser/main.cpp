#include "sgg/graphics.h"
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