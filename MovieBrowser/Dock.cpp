#include "Dock.h"


//DONE

void Dock::update()
{
	//Function that continuously updates our dock

	// Get the current mouse state and convert the mouse position to canvas coordinates.
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

	if (contains(mouse_X, mouse_Y))	//If our mouse contains Dock's coordinates, we want the dock to come down
	{
		if (m_dock_state == m_dock_status::STATE_IDLE)
		{
			m_dock_state = m_dock_status::STATE_GOING_DOWN;
			setActionTriggered(true);	//Alert that the dock is now coming down, so an action must be taken 
		}
		
		setOffset(-9.0f);	//Extending the area of the dock where our mouse can be.

		if (PlaySound)
		{
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("minimize.wav"), 0.5f);
		}

		//Giving our dock a height, basically the animation of it coming down.
		if (m_height != 6.0f)
		{
			m_height += 0.012f * graphics::getDeltaTime();

			if (m_height > 6.0f)
			{
				m_height = 6.0f;
			}
		}
	
		for (const auto& widget : widgets)
		{
			if (widget->m_height != widget->getHeightOffset())
			{
				widget->setVisibility(true);

				widget->m_height += 0.01f * graphics::getDeltaTime();

				if (widget->m_height > widget->getHeightOffset())
				{
					widget->m_height = widget->getHeightOffset();
				}
			}
		}
		PlaySound = false;
	}
	else if (!contains(mouse_X, mouse_Y))	//If our mouse doesn't contain Dock's borders, we want it to come up
	{
		if (m_dock_state == m_dock_status::STATE_IDLE)
		{
			return;
		}

		if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
		{
			m_dock_state = m_dock_status::STATE_GOING_UP;
			setActionTriggered(true);	//Alert that the dock is now coming up, so an action must be taken

			setOffset(-16.0f);	//Restoring the area where are mouse can be on the Dock, since now it's going up. 
			PlaySound = true;
		}

		//Restoring dock's height 
		if (m_height != 0.0f)
		{
			m_height -= 0.01f * graphics::getDeltaTime();
			if (m_height < 0.5f)
			{
				m_height = 0.0f;
				m_dock_state = m_dock_status::STATE_IDLE;
			}
		}
	
		//Restoring widgets's height
		for (const auto& widget : widgets)
		{
			if (widget->m_height == 0)
			{
				widget->m_height = 0;
				widget->setVisibility(false);
			}
			else
			{
				widget->m_height -= 0.01f * graphics::getDeltaTime();

				if (widget->m_height < 0.0f)
				{
					widget->m_height = 0.0f;
				}
			}

		}

	}

}

//Function that continuously draws our dock

void Dock::draw()
{
	graphics::setOrientation(180);
	brush.fill_opacity = 0.95f;
	brush.outline_opacity = 0.0f;
	brush.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::DOCK);
	graphics::drawRect(m_positionX, m_positionY + m_height, m_dock_width, m_dock_height, brush);
	graphics::resetPose();
}

//Constructs a new Dock
//   @param float x: The x-coordinate of the dock's position.
//   @param float y: The y-coordinate of the dock's position.
//   @param const std::vector<Widget*>& widgets_list: A reference to a vector of pointers to Widget objects.

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

// Checks if the mouse is within the boundaries of the dock
	// @param mouse_x: the x-coordinate of the mouse
	// @param mouse_y: the y-coordinate of the mouse
	// @return: true if the mouse is within the dock's boundaries, false otherwise

bool Dock::contains(float mouse_x, float mouse_y) const
{
	return (mouse_x > m_positionX - m_dock_width / 2 && mouse_x < m_positionX + m_dock_width / 2 && mouse_y > m_positionY + m_height - m_dock_height / 2 && mouse_y < m_positionY + m_height + m_dock_height / 2);
}

// Filters the movies using the `movie_list` when the dock is hovered or sliding up or down, also sets visibility true/false whether the dock is going down/up
	// @param movie_list: a vector of all the movies to be filtered

void Dock::takeAction(const std::vector<Movie*>& movie_list)
{
	if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
	{
		for (const auto& movie : movie_list) {

			movie->state_info.setUpdatable(false); //Setting our to not be active, which means it still can be drawn, but it is not being updated.
		}

	}

	else if (m_dock_state == m_dock_status::STATE_GOING_UP)
	{
		for (const auto& movie : movie_list) {

			movie->state_info.setUpdatable(true); //Setting our to be active, which means it can now be drawn and updated.
		}
	}
	setActionTriggered(false);	//Since we are done with the operation, alerting it.
	setOperating(false);

}
// Resets the dock's state
void Dock::clear()
{
}
