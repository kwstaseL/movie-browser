#include "Slider.h"

// Continously updates the state of the slider.
void Slider::update()
{
    // If the slider is invisible, return.
    if (!m_visible)
    {
        return;
    }

    //Getting the current mouse state and convert the mouse position to canvas coordinates.
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

            //Calculates the value of the m_value based on the box's slider position.
            // Adds the minimum value of our slider + (the current position of our box - the start of our slider) divided by the subtraction of our 
            // 2 horizantal "borders"  of the slider  which when subtracted it gives as the length of our slider
            // (This division finds in what "percentage" of our whole slider our slider button is at the moment) after we find that we multiply it by all the discrete values we can get
            // and adding that to the minimum value we have set to get our final value for that specific location of the button
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
    graphics::Brush br;
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(m_positionX - 4.5f, m_positionY + m_height + 0.115f, 0.3f, m_text, br);

    brush.texture = "";
    brush.fill_opacity = 0.1;
    brush.outline_opacity = .5f;
    graphics::drawRect(m_positionX, m_positionY + m_height, 7.0f, .0001f, brush);

    // Draw the 2 boxes for the sliders.
    br.texture = "";
    graphics::drawRect(box.getPosX(), box.getPosY() + m_height, box.getBoxWidth(), box.getBoxHeight(), br);

    graphics::drawText(box.getPosX() - 0.25f, box.getPosY() + m_height - 0.3f, 0.3f, std::to_string((m_value)), br);


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
    // Filter the list of movies based on the year on the slider, and taking into consideration all the other filters that might be active.
    filterByYear(movie_list);
}

// Clears the slider
void Slider::clear()
{
    if (m_slider_position_type == SliderPosition::Type::FROM)
    {
        m_value = m_min_value;
        box.setPosX(m_positionX - 3.5f);
        box.setPosY(m_positionY + 0.05f);

    }
    else if (m_slider_position_type == SliderPosition::Type::TO)
    {
        m_value = m_max_value;
        box.setPosX(m_positionX + 3.5f);
        box.setPosY(m_positionY + 0.05f);
    }
    m_status_slider = SLIDER_IDLE;
}

// Filter the list of movies based on the year on the slider, 
// and taking into consideration all the other filters that might be active for a specfic movie.

void Slider::filterByYear(const std::vector<Movie*>& movie_list)
{
    if (m_slider_position_type == SliderPosition::Type::FROM)
    {
        for (const auto& movie : movie_list)
        {
            //Here we are checkinng if the specific movie hasRequirements, and its years movie is between the sliders state
            if (std::stoi(movie->getDate()) >= m_value && std::stoi(movie->getDate()) <= (movie->state_info.getLastSelectedToYear())
                && hasRequirements(movie))
            {
                movie->state_info.setDisabled(false);
            }
            else
            {
                movie->state_info.setDisabled(true);
            }
            movie->state_info.setLastSelectedFromYear(m_value);    //Updating the last year that was filtered from the first slider
        }

    }
    else if (m_slider_position_type == SliderPosition::Type::TO)
    {
        for (const auto& movie : movie_list)
        {   //Here we are checkinng if the specific movie hasRequirements, and its years movie is between the sliders state
            if (std::stoi(movie->getDate()) <= m_value && (std::stoi(movie->getDate()) >= movie->state_info.getLastSelectedFromYear()) &&
                !(movie->state_info.getLastSelectedFromYear() > m_value) && hasRequirements(movie))
            {
                movie->state_info.setDisabled(false);
            }
            else
            {
                movie->state_info.setDisabled(true);

            }
            movie->state_info.setLastSelectedToYear(m_value);  //Updating the last year that was filtered from the second slider
        }
    }
    m_action = false;
    m_operating = false;
    m_status_slider = SLIDER_IDLE;
}

/*
Checks if the given movie meets the requirements for filtering (checks if it is filtered by other widgets),
 used to sychronize all filters with all widgets that can filter, together.
 \param movie: a pointer to the movie
 \return true if the movie meets the requirements
*/
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


Slider::Slider(float posX, float posY, const std::string_view text,int min_v,int max_v, SliderPosition::Type position, bool invisible)
    : Widget(posX, posY), m_text{ text }, m_min_value{ min_v }, m_max_value{ max_v }, m_slider_position_type{ position }
{
    clear();
    m_visible = !invisible;
    //Inserting all the widgetfilters slider needs to check before filtering
    filterToBeChecked.push_back(WidgetEnums::WidgetFilters::GenreFilter);
    filterToBeChecked.push_back(WidgetEnums::WidgetFilters::TitleFilter);
}