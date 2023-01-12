#include "ResetFilterButton.h"


/*
* Resets all movie control variables to their default values.
*
* \param movie_list A list of movies to apply the reset to.
*/
void ResetFilterButton::resetFilter(const std::vector<Movie*>& movie_list) const
{
    for (const auto& movie : movie_list)
    {
        movie->state_info.setDisabled(false);

        movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::GenreFilter, WidgetEnums::WidgetFilterState::ENABLED);
        movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::ENABLED);

        movie->state_info.setLastFilterFromYear(1950);
        movie->state_info.setLastFilterToYear(2020);
    }
}

/*
* Called when the reset filter button is clicked.
* Resets all applied filters.
*
* \param movie_list A list of movies to apply the reset to.
*/
void ResetFilterButton::takeAction(const std::vector<Movie*>& movie_list)
{
    resetFilter(movie_list);
}

//Continuously updates the reset filter button.
void ResetFilterButton::update()
{
    // Giving our widget a height so when the dock comes down, our button also comes down

    // If the reset filter button is invisible, dont update it.

    if (!m_visible)
    {
        return;
    }

    // Get mouse state
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse position to canvas coordinates
    mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
    mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

    // Check if mouse is inside button
    if (contains(mouse_X, mouse_Y))
    {
        // Mouse is inside button
        m_button_state = button_state_t::BUTTON_HIGHLIGHTED;
        m_highlighted = true;

        // Check if mouse button is pressed
        if (ms.button_left_pressed)
        {
            if (!requestFocus())    //Request for operation
            {
                return;
            }

            m_button_state = button_state_t::BUTTON_PRESSED;
            graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("button.wav"), 0.5f);
            setActionTriggered(true);
        }

        // Check if mouse button was released
        if (ms.button_left_released)
        {
            // Button was pressed and now is released
            m_button_state = button_state_t::BUTTON_IDLE;
            setActionTriggered(false);
            releaseFocus();     //Releasing request for operation
            setOperating(false);
        }
    }
    else
	{
		m_highlighted = false;
	}
}

// Continuously draws the reset filter button.
void ResetFilterButton::draw()
{

    // If the reset filter button is invisible, dont draw it.
	if (!m_visible)
	{
		return;
	}
	float highlight = 0.8f * m_highlighted;

    //Drawing highlight animation
	SETCOLOR(brush.fill_color, 0.8f * highlight, 0.8f * highlight, 0.8f * highlight);
	brush.outline_opacity = 0.5f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width + 0.1, m_Genrebutton_height + 0.1, brush);

    //Drawing text of button
	brush.fill_opacity = 1.0f;
	SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(m_positionX - 0.75f, m_positionY + 0.125f + m_height, 0.4f, m_button_text, brush);

	SETCOLOR(brush.fill_color, 1.0f, 0.0f, 0.0f);

	//Drawing our button
	brush.texture = "";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.2f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width, m_Genrebutton_height, brush);
}


void ResetFilterButton::clear()
{
}

/*
* Constructs a new ResetFilterButton at the given position with the given text.
* \param posX The x-coordinate of the button's position.
* \param posY The y-coordinate of the button's position.
* \param text The text to display on the button.
*/
ResetFilterButton::ResetFilterButton(float posX, float posY, const std::string_view text)
	: Button(posX, posY, text)
{}