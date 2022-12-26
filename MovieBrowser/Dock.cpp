#include "Dock.h"

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

		height += 0.01f * graphics::getDeltaTime();

		if (height > 6.0f)
		{
			height = 6.0f;
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
		height -= 0.01f * graphics::getDeltaTime();
		if (height < 0.5f)
		{
			height = 0.0f;
		}
	}
	else
	{
		m_dock_state = m_dock_status::STATE_IDLE;
	}


}


void Dock::draw()
{

	graphics::setOrientation(180);
	brush.fill_opacity = 0.95f;
	brush.outline_opacity = 0.0f;
	brush.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::DOCK);
	graphics::drawRect((CanvasConst::CANVAS_WIDTH / 2), -3.6f + height, m_positionX, m_positionY, brush);
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

bool Dock::contains(float x, float y) const
{

	return FunctionsConst::distance(x, y, m_positionX - 0.8f, m_positionY + m_offset - 1.0f) < ((((CanvasConst::CANVAS_WIDTH) / 2) + 5.0f)) / 2;

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
