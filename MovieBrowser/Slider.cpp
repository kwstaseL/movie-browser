#include "Slider.h"


// Continously updates the state of the slider.

void Slider::update()
{
    //If the slider is invisible, return.
    if (!m_visible)
    {
        return;
    }

    //Gettng the current mouse state and convert the mouse position to canvas coordinates.
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
    mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);


    //Saves the current position of the box to temp variable.
    int temp{ box.getPosX() };

    // Check if the mouse is within the coordinates of the slider or if the slider is being dragged.
    // We want the box to be able to be dragged even if doesn't contains box's coordinates
    if (contains(mouse_X, mouse_Y) || m_status_slider == SLIDER_DRAGGING)
    {
        // If the mouse is being dragged, update the position of the box and the year based on the change in position.
        if (ms.dragging)         
        {
            box.setActive(true);

            if (!requestFocus())
            {
                return;
            }
            // Check if the mouse is going out of the bounds of the slider.
            if (mouse_X >= 16.0f && box.getPosX() >= 16.0f)
            {
                mouse_X = 16.0f;
                m_year = 2020;
            }
            // Check if the mouse is going out of the bounds of the slider.
            if (mouse_X <= m_positionX - 2.9f && box.getPosX() <= m_positionX - 2.9f)
            {
                mouse_X = m_positionX - 2.9f;
                m_year = 1950;
            }

            box.setPosX(mouse_X);

            m_status_slider = SLIDER_DRAGGING;

            // Update the year based on the change in position of the box.

            if (temp < box.getPosX())
            {
                m_year += 10;
            }
            else if (temp > box.getPosX())
            {
                m_year -= 10;
            }
            else {

                m_year += 0;
            }

            // Enforcing bounds on the position of the box.
            if (box.getPosX() >= m_positionX + 3.5f)
            {
                box.setPosX(m_positionX + 3.5f);
            }
            if (box.getPosX() <= m_positionX - 2.9f)
            {
                box.setPosX(m_positionX - 2.9f);
            }
        }   // If the mouse button is released and the slider was being dragged, release focus and set the action as triggered.
        else if ((ms.button_left_released || !ms.dragging) && m_status_slider == SLIDER_DRAGGING)
        {
            releaseFocus();
            m_status_slider = SLIDER_RELEASED;
            box.setActive(true);
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
    if (m_uid == 9) //From
    {
        br.texture = "";
        graphics::drawRect(box.getPosX() + 0.1f, box.getPosY() + m_height + 0.3f, 0.2f, 0.5f, br);

        graphics::drawText(box.getPosX() - 0.25f, box.getPosY() + m_height, 0.3f, std::to_string((m_year)), br);

    }
    else //To
    {
        br.texture = "";
        graphics::drawRect(box.getPosX() + 0.1f, box.getPosY() + m_height + 0.6f, 0.2f, 0.5f, br);

        graphics::drawText(box.getPosX() - 0.25f, box.getPosY() + m_height + 0.3f, 0.3f, std::to_string((m_year)), br);
    }



}
//Checks if the mouse is within the coordinates of the boxes slider
// \param mouse_x: the x coordinate of the mouse
// \param mouse_y: the y coordinate of the mouse
// \return true if the mouse is within the boxes slider coordinates
bool Slider::contains(float mouse_x, float mouse_y) const
{

    if (m_uid == 9) //From
    {

        return (mouse_x > box.getPosX() + 0.1f - 0.2f / 2 && mouse_x < box.getPosX() + 0.1f + 0.2f / 2 && mouse_y > box.getPosY() + m_height + 0.3f - 0.5f / 2 && mouse_y < box.getPosY() + m_height + 0.3f + 0.5f / 2);
    }

    if (m_uid == 10)    //To
    {
     
        return (mouse_x > box.getPosX() + 0.1f - 0.2f / 2 && mouse_x < box.getPosX() + 0.1f + 0.2f / 2 && mouse_y > box.getPosY() + m_height + 0.6f - 0.5f / 2 && mouse_y < box.getPosY() + m_height + 0.6f + 0.5f / 2);

    }

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
    if (m_uid == 9)
    {
        m_year = 1950;
        box.setPosX(m_positionX - 2.9f);
        box.setPosY(m_positionY - 0.56f);

    }
    else
    {
        m_year = 2020;
        box.setPosX(16.0f);
        box.setPosY(m_positionY - 0.56f);
    }
    m_status_slider = SLIDER_IDLE;
}

// Filter the list of movies based on the year on the slider, 
// and taking into consideration all the other filters that might be active for a specfic movie.

void Slider::filterByYear(const std::vector<Movie*>& movie_list)
{
    if (m_uid == 9) //From >= m_year
    {
        for (const auto& movie : movie_list)
        {
            //Here we are checkinng if the specific movie hasRequirements, and its years movie is between the sliders state
            if (std::stoi(movie->getDate()) >= m_year && std::stoi(movie->getDate()) <= (movie->state_info.getLastFilterToYear())
                && hasRequirements(movie))
            {
                movie->state_info.setDisabled(false);
            }
            else
            {
                movie->state_info.setDisabled(true);
            }
            movie->state_info.setLastFilterFromYear(m_year);    //Updating the last year that was filtered from the first slider
        }

    }
    else if (m_uid == 10) // To
    {
        for (const auto& movie : movie_list)
        {   //Here we are checkinng if the specific movie hasRequirements, and its years movie is between the sliders state
            if (std::stoi(movie->getDate()) <= m_year && (std::stoi(movie->getDate()) >= movie->state_info.getLastFilterFromYear()) &&
                !(movie->state_info.getLastFilterFromYear() > m_year) && hasRequirements(movie))
            {
                movie->state_info.setDisabled(false);
            }
            else
            {
                movie->state_info.setDisabled(true);

            }
            movie->state_info.setLastFilterToYear(m_year);  //Updating the last year that was filtered from the second slider
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


Slider::Slider(float posX, float posY, const std::string_view text)
    : Widget(posX, posY), m_text{ text }
{
    clear();

    //Inserting all the widgetfilters slider needs to check before filtering
    filterToBeChecked.push_back(WidgetEnums::WidgetFilters::GenreFilter);
    filterToBeChecked.push_back(WidgetEnums::WidgetFilters::TitleFilter);
}