#include "ResetFilterButton.h"


//Continuously updates the reset filter button.
void ResetFilterButton::update()
{
    // Giving our widget a height so when the dock comes down, our button also comes down

    // If the reset filter button is invisible, dont update it.
    //(+ if button is IDLE can also be added here, if we have a button that might not be invisible)
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
            graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("button.wav"), SOUND_VOLUME);
            m_action = true;
        }

        // Check if mouse button was released
        if (ms.button_left_released)
        {
            // Button was pressed and now is released
            m_button_state = button_state_t::BUTTON_IDLE;
            m_action = false;
            releaseFocus();     //Releasing request for operation
            m_operating = false;
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
    
    const float HIGHLIGHT_COLOR_FACTOR{ 0.8f };
    float highlight = HIGHLIGHT_COLOR_FACTOR * m_highlighted;

    //Drawing highlight animation
    const float BUTTON_OUTLINE_THICKNESS{ 0.1f };

    SETCOLOR(brush.fill_color, HIGHLIGHT_COLOR_FACTOR * highlight, HIGHLIGHT_COLOR_FACTOR * highlight, HIGHLIGHT_COLOR_FACTOR * highlight);
    brush.outline_opacity = 0.5f;
    graphics::drawRect(m_positionX, m_positionY + m_height, m_button_width + BUTTON_OUTLINE_THICKNESS, m_button_height + BUTTON_OUTLINE_THICKNESS, brush);

    //Drawing text of button
    const float TEXT_POSITION_X_OFFSET{ 0.75f };
    const float TEXT_POSITION_Y_OFFSET{ 0.125f };

    brush.fill_opacity = 1.0f;
    SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(m_positionX - TEXT_POSITION_X_OFFSET, m_positionY + TEXT_POSITION_Y_OFFSET + m_height, 0.4f, m_button_text, brush);

    //Drawing our button
    SETCOLOR(brush.fill_color, 1.0f, 0.0f, 0.0f);
    brush.texture = "";
    brush.fill_opacity = 1.0f;
    brush.outline_opacity = 0.2f;
    graphics::drawRect(m_positionX, m_positionY + m_height, m_button_width, m_button_height, brush);
}

/*
*  Called when the reset filter button is clicked.
*  Resets all applied filters and all other widgets clear their own state.
*  \param movie_list A list of our movies.
*/
void ResetFilterButton::takeAction(const std::vector<Movie*>& movie_list)
{
    restoreMovieStates(movie_list);
    clearWidgets();
}

/*
 * Resets all movie filter widgets to their default values and enables all movies.
 * When this function gets called, each widget will "clear" all their own states automatically.
 *
 * \param movie_list A list of our movies
 */
void ResetFilterButton::restoreMovieStates(const std::vector<Movie*>& movie_list) const
{
    for (const auto& movie : movie_list)
    {
        movie->state_info.resetMovieState();
    }
}

void ResetFilterButton::clearWidgets()
{
    for (const auto& widget : m_widgets)
    {
        widget->clear();
    }
}


void ResetFilterButton::clear()
{}

/*
* Constructs a new ResetFilterButton.
* \param posX The x coordinate of the button's position.
* \param posY The y coordinate of the button's position.
* \param text The text to display on the button.
*/
ResetFilterButton::ResetFilterButton(float posX, float posY, const std::string_view text, const std::vector<Widget*>& widgets, bool invisible)
	: Widget(posX,posY) , Button(text), m_widgets{widgets}
{
    m_visible = !invisible;
}