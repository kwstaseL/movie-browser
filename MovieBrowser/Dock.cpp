#include "Dock.h"

//Function that continuously updates our dock
void Dock::update()
{

	// Get the current mouse state and convert the mouse position to canvas coordinates.
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

	if (contains(mouse_X, mouse_Y))	//If our mouse contains Dock's coordinates, we want the dock to come down
	{
		if (m_dock_state == m_dock_status::STATE_IDLE || m_dock_state == m_dock_status::STATE_GOING_UP)	//If the state previously was IDLE, or the Dock was Previously going up
		{
			m_dock_state = m_dock_status::STATE_GOING_DOWN;

			if (m_height != 6.0f)
			{
				m_action = true;	//Alert the GUI that the dock is now coming down, so an action must be taken 
			}
		}
		
		m_offset = -9.0f;	//Extending the area of the dock where our mouse can be.

		if (PlaySound)
		{
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("minimize.wav"), 0.5f);
		}

		//Giving our dock a height, basically the animation of it coming down.
		if (m_height != 6.0f)
		{
			//On each update, we increase dock's height multiplied by getDeltaTime which
			//is the time passed from the previous state update
			m_height += 0.012f * graphics::getDeltaTime();

			if (m_height > 6.0f)
			{
				m_height = 6.0f;
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
				widget->m_height += 0.008f * graphics::getDeltaTime();

				if (widget->m_height > widget->getHeightOffset())	//If the height of a particular widget is where it should be then set it to be there.
				{
					widget->m_height = widget->getHeightOffset();
				}
			}
		}
		PlaySound = false;
	}
	else if (!contains(mouse_X, mouse_Y))	// If our mouse doesn't contain Dock's coordinates, we want it to come up
	{

		if (m_dock_state == m_dock_status::STATE_IDLE)	// If mouse doesnt contain Dock's coordinates and the state is IDLE , return.
		{
			return;
		}

		if (m_dock_state == m_dock_status::STATE_GOING_DOWN)
		{
			m_dock_state = m_dock_status::STATE_GOING_UP;
			m_action = true;	// Alert that the dock is now coming up, so an action must be taken

			m_offset = -16.0f;	//Restoring the area where are mouse can be on the Dock, since now it's going up. 
			PlaySound = true;
		}

		//Restoring dock's height 
		if (m_height != 0.0f)
		{
			//On each update, we decrease dock's height multiplied by getDeltaTime which
			//is the time passed from the previous state update
			m_height -= 0.01f * graphics::getDeltaTime();
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
				allWidgetsUp = true;
			}
			else
			{
				allWidgetsUp = false;
				//On each update, we decrease all widget's height multiplied by getDeltaTime which
				//is the time passed from the previous state update
				widget->m_height -= 0.01f * graphics::getDeltaTime();	 

				if (widget->m_height < 0.0f)	//If the height of a particular widget is where it should be (0) then set it to be there.
				{
					widget->m_height = 0.0f;
				}
			}
		}

		//If the action is already done (set all movies to updatable) and the dock and the widgets are restored
		// to their default height, then set the state as idle.
		if (!m_action && m_height == 0 && allWidgetsUp)
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
	graphics::drawRect(m_positionX, m_positionY + m_height, m_dock_width, m_dock_height, brush);	//Drawing the Dock.
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
		if (widget)
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

			movie->state_info.setUpdatable(false); //Setting our to not be active, which means it still can be drawn, but it is not being updated.
		}
	}
	else if (m_dock_state == m_dock_status::STATE_GOING_UP)
	{
		for (const auto& movie : movie_list) {

			movie->state_info.setUpdatable(true); //Setting our to be active, which means it can now be drawn and updated.
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
