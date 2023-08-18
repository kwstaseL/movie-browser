#include "Slider.h"

// Continously updates the state of the slider.
void Slider::update()
{
    // If the slider is invisible, return.
    if (!m_visible)
    {
        return;
    }

    // Getting the current mouse state and convert the mouse position to canvas coordinates.
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
    mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

    // Check if the mouse is within the coordinates of the slider or if the slider is being dragged.
    // We want the button to be able to be dragged even if it doesn't contain the button's coordinates
    if (contains(mouse_X, mouse_Y) || m_status_slider == SLIDER_DRAGGING)
    {
        // If the mouse is being dragged, update the position of the button and the value based on the change in position.
        if (ms.dragging)
        {
            if (!requestFocus())
            {
                return;
            }
            // Check if the mouse and the box is going out of the bounds of the slider. (checking for end of slider) 
            if (mouse_X >= SLIDER_START_RANGE && box.getPosX() >= SLIDER_START_RANGE)
            {
                mouse_X = SLIDER_START_RANGE;
                m_value = m_max_value;
            }
            // Check if the mouse and the box is going out of the bounds of the slider. (checking for start of slider) 
            if (mouse_X <= SLIDER_END_RANGE && box.getPosX() <= SLIDER_END_RANGE)
            {
                mouse_X = SLIDER_END_RANGE;
                m_value = m_min_value;
            }

            box.setPosX(mouse_X);   //Setting to the box the position of our mouse horizontally

            m_status_slider = SLIDER_DRAGGING;

            // Calculates the value of m_value based on the position of the box slider.
            // It determines the position of the slider button within the slider's range,
            // and maps it to the corresponding value within the minimum and maximum value range.
            // The formula involves normalizing the slider position as a percentage of the total slider length,
            // and then scaling that percentage to the appropriate value range.
            // The resulting value represents the current value based on the button's position.
            m_value = m_min_value + (box.getPosX() - SLIDER_END_RANGE) / (SLIDER_START_RANGE - SLIDER_END_RANGE) * (m_max_value - m_min_value);
        }
         else if ((ms.button_left_released || !ms.dragging) && m_status_slider == SLIDER_DRAGGING)
        {
            releaseFocus();
            m_status_slider = SLIDER_RELEASED;
            m_action = true; //Alerting GUI to take an action on the slider
        }
    }
}

// Continuously draws the slider on the canvas.
void Slider::draw()
{

    //If the slider is invisible, return.
    if (!m_visible)
    {
        return;
    }

    //Drawing Line
    constexpr float LINE_POSX_OFFSET{ -4.5f };
    constexpr float LINE_POSY_OFFSET{ 0.115f };

    graphics::Brush br;
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(m_positionX + LINE_POSX_OFFSET, m_positionY + m_height + LINE_POSY_OFFSET, 0.3f, m_text, br);

    const float LINE_WIDTH{ 7.0f };
    const float LINE_HEIGHT{ .0001f };
    brush.texture = "";
    brush.fill_opacity = 0.1;
    brush.outline_opacity = .5f;
    graphics::drawRect(m_positionX, m_positionY + m_height, LINE_WIDTH, LINE_HEIGHT, brush);

    // Draw the 2 boxes for the sliders.

    constexpr float BOXTEXT_POSX_OFFSET{ -0.25f };
    constexpr float BOXTEXT_POSY_OFFSET{ -0.3f };

    br.texture = "";
    graphics::drawRect(box.getPosX(), box.getPosY() + m_height, box.getBoxWidth(), box.getBoxHeight(), br);
    graphics::drawText(box.getPosX() + BOXTEXT_POSX_OFFSET, box.getPosY() + m_height + BOXTEXT_POSY_OFFSET, 0.3f, std::to_string((m_value)), br);


}
//Checks if the mouse is within the coordinates of the boxes slider
// \param mouse_x: the x coordinate of the mouse
// \param mouse_y: the y coordinate of the mouse
// \return true if the mouse is within the boxes slider coordinates
bool Slider::contains(float mouse_x, float mouse_y) const
{

    return (mouse_x > box.getPosX() - box.getBoxWidth() / 2 && mouse_x < box.getPosX() + box.getBoxWidth() / 2 
        && mouse_y > box.getPosY() + m_height - box.getBoxHeight() / 2 && mouse_y < box.getPosY() + m_height + box.getBoxHeight() / 2);
    
}
// This is the function which runs the filterByYear when the box is dragged and released
void Slider::takeAction(const std::vector<Movie*>& movie_list)
{
    // Filter the list of movies based on the year on the slider,
    // and taking into consideration all the other filters that might be active.
    filterByYear(movie_list);
}
//Clears the slider
void Slider::clear()
{
    if (m_slider_position_type == SliderPosition::Type::FROM)
    {
        m_value = m_min_value;
        box.setPosX(m_positionX - SLIDER_BOX_X_OFFSET);
        box.setPosY(m_positionY + SLIDER_BOX_Y_OFFSET);
    }
    else if (m_slider_position_type == SliderPosition::Type::TO)
    {
        m_value = m_max_value;
        box.setPosX(m_positionX + SLIDER_BOX_X_OFFSET);
        box.setPosY(m_positionY + SLIDER_BOX_Y_OFFSET);
    }
    m_status_slider = SLIDER_IDLE;
}

// Filter the list of movies based on the year on the slider, 
// and taking into consideration all the other filters that might be active for a specfic movie.
void Slider::filterByYear(const std::vector<Movie*>& movie_list)
{
    //Iterate through the list of movies to apply the year-based filtering
    for (auto& movie : movie_list)
    {
        // Skip movies that don't meet other filter requirements
        if (!hasRequirements(movie))
        {
            continue;
        }

        // Extract the release year of the movie
        int movieYear = std::stoi(movie->getDate());

        // Determine the year of the other slider based on the slider type
        int otherSliderYear = (m_slider_position_type == SliderPosition::Type::FROM)
            ? movie->state_info.getLastSelectedToYear()
            : movie->state_info.getLastSelectedFromYear();

        if (m_slider_position_type == SliderPosition::Type::FROM)
        {
            // Disable the movie if its year is outside the selected range
            movie->state_info.setDisabled(movieYear < m_value || movieYear > otherSliderYear);
            // Update the last selected "from" year
            movie->state_info.setLastSelectedFromYear(m_value);
        }
        else if (m_slider_position_type == SliderPosition::Type::TO)
        {
            //Disable the movie if its year is outside the selected range
            // or if the other slider's "from" year is outside the current range
            movie->state_info.setDisabled(movieYear > m_value || movieYear < otherSliderYear || otherSliderYear > m_value);
            movie->state_info.setLastSelectedToYear(m_value);
        }
    }
    m_action = false;
    m_operating = false;
    m_status_slider = SLIDER_IDLE;
}



bool Slider::hasRequirements(const Movie* movie) const
{
    if (movie)
    {
        for (const auto& key : filterToBeChecked)
        {
            if (movie->state_info.getWidgetState(key) != WidgetEnums::WidgetFilterState::ENABLED)
            {
                return false;
            }
        }
        return true;
    }
}


Slider::Slider(float posX, float posY, const std::string_view text,int min_v,
    int max_v, SliderPosition::Type position, bool invisible)
    : Widget(posX,posY), FilterableWidget(invisible), m_text{ text }, m_min_value{ min_v }, m_max_value{ max_v }, m_slider_position_type{ position }
{
    clear();

    //Inserting all the widgetfilters slider needs to check before filtering
    filterToBeChecked.push_back(WidgetEnums::WidgetFilters::GenreFilter);
    filterToBeChecked.push_back(WidgetEnums::WidgetFilters::TitleFilter);
}