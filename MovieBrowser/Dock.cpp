#include "Dock.h"

//DONE

void Dock::update()
{
	
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);
	
	if (contains(mouse_X, mouse_Y)) 
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
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::DOCK);
	graphics::drawRect((CanvasConst::CANVAS_WIDTH / 2), -3.6f+ height, m_posX, m_posY, br);
	graphics::resetPose();										
	
}

bool Dock::contains(float x, float y) const
{
	
	return FunctionsConst::distance(x, y, m_posX+0.7f, m_posY+m_offset) < ((((CanvasConst::CANVAS_WIDTH) / 2) + 3.6f))/2;

}
