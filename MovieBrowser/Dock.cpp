#include "Dock.h"
#include <iostream>

void Dock::update()
{

	graphics::MouseState ms;
	graphics::getMouseState(ms);	//Fills our ms state, ms inside has states of our mouse , button left pressed, button left down..

	float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
	float my{ graphics::windowToCanvasY(ms.cur_pos_y) };

	//Going with my mouse to movie images , mouse_x and mouse_y is on the image if they are on movie's "zone"

	
	if (contains(mx, my)) 
	{
		Pressed = true;
		setOffset(-9.0f);
		if (PlaySound)
		{
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("minimize.wav"), 0.5f);
		}
		height += 0.01f*graphics::getDeltaTime();
		if (height > 6.0f)
		{
			height = 6.0f;
		}
		PlaySound = false;
	}
	else
	{
		Pressed = false;
		setOffset(-16.0f);
		PlaySound = true;
		height -= 0.01f * graphics::getDeltaTime();
		if (height < 0.5f)
		{
			height = 0.0f;
		}
	}

}


void Dock::draw() const
{


		graphics::Brush br;
		graphics::setOrientation(180);
		//graphics::setScale(height, height);
		br.fill_opacity = 1.0f;
		br.outline_opacity = 0.0f;
		br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::DOCK);
		graphics::drawRect((CanvasConst::CANVAS_WIDTH / 2), -3.6f+ height, m_posX, m_posY, br);
		graphics::resetPose();										

	
	
}

bool Dock::contains(float x, float y) const
{
	
	return FunctionsConst::distance(x, y, m_posX-1.0f, m_posY+m_offset) < ((((CanvasConst::CANVAS_WIDTH) / 2) + 3.6f))/2;

}
