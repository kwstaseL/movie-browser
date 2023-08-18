#include "Dock.h"

// Function that handles dock animation and widget height adjustments
void Dock::update()
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
    mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

    bool mouseOverDock = contains(mouse_X, mouse_Y);

    if (mouseOverDock)
    {
        // Handle dock going down animation
        if (m_dock_state == m_dock_status::IDLE || m_dock_state == m_dock_status::GOING_UP)
        {
            m_dock_state = m_dock_status::GOING_DOWN;
            m_action = (m_height != DOCK_ANIMATION_SPEED);
        }

        if (playSound)
        {
            graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("minimize.wav"), SOUND_VOLUME);
        }

        // Increase dock height with animation speed, ensuring it doesn't exceed max height
        m_height = std::min(m_height + DOCK_ANIMATION_SPEED * graphics::getDeltaTime(), MAX_DOCK_HEIGHT);

        // Adjust widget heights if they are not at their target height
        for (const auto& widget : widgets)
        {
            if (widget->m_height != widget->getHeightOffset())
            {
                widget->setVisibility(true);
                widget->m_height = std::min(widget->m_height + WIDGET_ANIMATION_SPEED * graphics::getDeltaTime(), widget->getHeightOffset());
            }
        }
        playSound = false;
    }
    else
    {
        if (m_dock_state == m_dock_status::IDLE)
        {
            return;
        }

        if (m_dock_state == m_dock_status::GOING_DOWN)
        {
            // Handle dock going up animation
            m_dock_state = m_dock_status::GOING_UP;
            m_action = true;
            playSound = true;
        }

        // Decrease dock height with restoration speed, ensuring it doesn't go below 0
        m_height = std::max(m_height - WIDGET_RESTORE_SPEED * graphics::getDeltaTime(), 0.0f);

        bool widgetsResetted = true;

        // Restore widget heights and adjust their visibility
        for (const auto& widget : widgets)
        {
            if (widget->m_height != 0.0f)
            {
                widgetsResetted = false;
                widget->m_height = std::max(widget->m_height - WIDGET_RESTORE_SPEED * graphics::getDeltaTime(), 0.0f);
                widget->setVisibility(widget->m_height > 0.0f);
            }
        }

        // If action is done and dock and widgets are reset to default height, set state to idle
        if (!m_action && m_height == 0 && widgetsResetted)
        {
            m_dock_state = m_dock_status::IDLE;
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
    for (const auto& movie : movie_list)
    {
        //Setting our to not be active, which means it still can be drawn, but it is not being updated.
        movie->state_info.setInformationVisible(m_dock_state != m_dock_status::GOING_DOWN);
    }
	m_action = false;	//Since we are donef with the operation, alert it.
	m_operating = false;
}

// Resets the dock's state
void Dock::clear()
{
	m_dock_state = m_dock_status::IDLE;
}
