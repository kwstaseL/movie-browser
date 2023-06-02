#include "Dock.h"

//Function that continuously updates our dock
void Dock::update()
{
	// Get the current mouse state and convert the mouse position to canvas coordinates.
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

	//If our mouse contains Dock's coordinates, we want the dock to come down
	if (contains(mouse_X, mouse_Y))	
	{
		//If the state previously was IDLE, or the Dock was Previously going up
		if (m_dock_state == m_dock_status::STATE_IDLE || m_dock_state == m_dock_status::STATE_GOING_UP)	
		{
			m_dock_state = m_dock_status::STATE_GOING_DOWN;

			if (m_height != dock_animation_speed)
			{
				//Alert the GUI that the dock is now coming down, so an action must be taken 
				m_action = true;	
			}
		}
		
		if (playSound)
		{
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("minimize.wav"), SOUND_VOLUME);
		}

		//Giving our dock a height, basically the animation of it coming down.
		if (m_height != max_dock_height)
		{
			//On each update, we increase dock's height multiplied by getDeltaTime which
			//is the time passed from the previous state update
			m_height += dock_animation_speed * graphics::getDeltaTime();

			if (m_height > max_dock_height)
			{
				m_height = max_dock_height;
			}
		}
		
		//Giving all our widgets a height, depending on their position on the dock , and setting them as visible
		for (const auto& widget : widgets)
		{
			if (widget->m_height != widget->getHeightOffset())
			{
				widget->setVisibility(true);

				//On each update, we increase all widget's height multiplied by getDeltaTime which
				//is the time passed from the previous state update
				widget->m_height += widget_animation_speed * graphics::getDeltaTime();

				//If the height of a particular widget is where it should be then set it to be there.
				if (widget->m_height > widget->getHeightOffset())	
				{
					widget->m_height = widget->getHeightOffset();
				}
			}
		}
		playSound = false;
	}
	// If our mouse doesn't contain Dock's coordinates, we want it to come up
	else if (!contains(mouse_X, mouse_Y))	
	{

		// If mouse doesnt contain Dock's coordinates and the state is IDLE , return.
		if (m_dock_state == m_dock_status::STATE_IDLE)	
		{
			return;
		}

		if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
		{
			// Alert that the dock is now coming up, so an action must be taken
			m_dock_state = m_dock_status::STATE_GOING_UP;
			m_action = true;	
			playSound = true;
		}

		//Restoring dock's height 
		if (m_height != 0.0f)
		{
			//On each update, we decrease dock's height multiplied by getDeltaTime which
			//is the time passed from the previous state update
			m_height -= widget_restore_speed * graphics::getDeltaTime();
			if (m_height < 0.5f)
			{
				m_height = 0.0f;
			}
		}
	
		//Restoring widgets's height and setting them as invisible
		for (const auto& widget : widgets)
		{
			if (widget->m_height == 0)
			{
				widget->m_height = 0;
				widget->setVisibility(false);
				widgetsResetted = true;
			}
			else
			{
				widgetsResetted = false;
				//On each update, we decrease all widget's height multiplied by getDeltaTime which
				//is the time passed from the previous state update
				widget->m_height -= widget_restore_speed * graphics::getDeltaTime();

				if (widget->m_height < 0.0f)	
				{
					widget->m_height = 0.0f;
				}
			}
		}

		//If the action is already done and the dock and the widgets are resetted
		// to their default height, then set the state as idle.
		if (!m_action && m_height == 0 && widgetsResetted)
		{
			m_dock_state = m_dock_status::STATE_IDLE;
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
	//Drawing the Dock.
	graphics::drawRect(m_positionX, m_positionY + m_height, m_dock_width, m_dock_height, brush);	
	graphics::resetPose();
}

//Constructs a new Dock
//  \param float x: The x coordinate of the dock's position.
//  \param float y: The y coordinate of the docks position.
//  \param const std::vector<Widget*>& widgets_list: a vector of our Widgets.
Dock::Dock(float x, float y, const std::vector<Widget*>& widgets_list)
	: Widget(x, y)
{
	for (const auto& widget : widgets_list)
	{
		if (widget && !widget->isVisible())
		{
			widgets.push_back(widget);
		}
	}
}


//Checks if the mouse is within the coordinates of the dock.
// \param mouse_x: the x coordinate of the mouse
// \param mouse_y: the y coordinate of the mouse
// \return true if the mouse is within the dock's coordinates
bool Dock::contains(float mouse_x, float mouse_y) const
{
	return (mouse_x > m_positionX - m_dock_width / 2 && mouse_x < m_positionX + m_dock_width / 2
		&& mouse_y > m_positionY + m_height - m_dock_height / 2 && mouse_y < m_positionY + m_height + m_dock_height / 2);
}


//Sets all movies as not updatable or updatable using the `movie_list` depending if the dock is going down or it's going up, 
// Not Updatable:  which means it still can be drawn, but information is not being updated or drawn about this movie, the movie can't be hovered over in general.
//\param movie_list: a vector of all our movies
void Dock::takeAction(const std::vector<Movie*>& movie_list)
{
	if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
	{
		for (const auto& movie : movie_list) {

			//Setting our to not be active, which means it still can be drawn, but it is not being updated.
			movie->state_info.setInformationVisible(false);
		}
	}
	else if (m_dock_state == m_dock_status::STATE_GOING_UP)
	{
		for (const auto& movie : movie_list) {

			//Setting our to be active, which means it can now be drawn and updated.
			movie->state_info.setInformationVisible(true); 
		}
	}
	m_action = false;	//Since we are donef with the operation, alert it.
	m_operating = false;
}

// Resets the dock's state
void Dock::clear()
{
	m_dock_state = m_dock_status::STATE_IDLE;
}
