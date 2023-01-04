#include "Dock.h"


//Updating the dock

void Dock::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

	if (contains(mouse_X, mouse_Y))
	{
		if (!(m_dock_state == m_dock_status::STATE_GOING_DOWN))
		{
			m_dock_state = m_dock_status::STATE_GOING_DOWN;
			setActionTriggered(true);
		}
		
		setOffset(-9.0f);

		if (PlaySound)
		{
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("minimize.wav"), 0.5f);
		}

		m_height += 0.01f * graphics::getDeltaTime();

		if (m_height > 6.0f)
		{
			m_height = 6.0f;
		}

		PlaySound = false;
	}
	else if (!contains(mouse_X, mouse_Y))
	{
		if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
		{
			m_dock_state = m_dock_status::STATE_GOING_UP;
			setActionTriggered(true);
		}
		
		setOffset(-16.0f);

		PlaySound = true;

		m_height -= 0.01f * graphics::getDeltaTime();
		if (m_height < 0.5f)
		{
			m_height = 0.0f;
		}
	}

}

//Drawing the dock

void Dock::draw()
{
	graphics::setOrientation(180);
	brush.fill_opacity = 0.95f;
	brush.outline_opacity = 0.0f;
	brush.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::DOCK);
	graphics::drawRect((CanvasConst::CANVAS_WIDTH / 2), -3.6f + m_height, m_positionX, m_positionY, brush);
	graphics::resetPose();

}


Dock::Dock(float x, float y, const std::vector<Widget*>& widgets_list)
	: Widget(x, y)
{
	for (const auto& widget : widgets_list)
	{
		if (widget)
		{
			if (widget == this)
			{
				continue;
			}
			widgets.push_back(widget);
		}
	}
}

bool Dock::contains(float mouse_x, float mouse_y) const
{

	return (mouse_x > (CanvasConst::CANVAS_WIDTH / 2) - m_positionX / 2 && mouse_x < (CanvasConst::CANVAS_WIDTH / 2) + m_positionX / 2 && mouse_y > -3.6f + m_height - m_positionY / 2 && mouse_y < -3.6f + m_height + m_positionY / 2);

}

void Dock::takeAction(const std::vector<Movie*>& movie_list)
{
	if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
	{
		for (const auto& widget : widgets)
		{
			widget->setVisibility(true);
		}
		for (const auto& movie : movie_list) {

			movie->setActive(false);

		}

	}
	else if (m_dock_state == m_dock_status::STATE_GOING_UP)
	{

		for (const auto& widget : widgets)
		{
			widget->setVisibility(false);
		}
		for (const auto& movie : movie_list) {

			movie->setActive(true);

		}

	}
	setActionTriggered(false);
	setOperating(false);
}

void Dock::clear()
{
}
