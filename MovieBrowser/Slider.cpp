#include "Slider.h"
#include <iostream>

//DONE

/*

To do:
1) Fix when from goes to end and to goes to start why is it drawing the movies?
2) when from goes to 1950 all movies appear

*/

void Slider::update()
{
    m_height += 0.008f * graphics::getDeltaTime();

    if (m_height > 4.0f)
    {
        m_height = 4.0f;
    }

    if (!m_visible)
    {
        m_height = 0.0f;
        return;
    }
 
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
    float my{ graphics::windowToCanvasY(ms.cur_pos_y) };


    //Based on slider id we will filter
    SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);

    int temp{ box.getPosX() };

    if (contains(mx, my))
    {
        box.setActive(true);

   
        if (ms.dragging && box.isActive())          //FIX THIS
        {
            if (!requestFocus())
            {
                return;
            }

            if (mx >= 16.0f && box.getPosX() >= 16.0f)
            {
                mx = 16.0f;
                m_year = 2020;
            }

            if (mx <= m_positionX - 2.9f && box.getPosX() <= m_positionX - 2.9f)
            {
                mx = m_positionX - 2.9f;
                m_year = 1950;
            }

            box.setPosX(mx);

            m_status_slider = SLIDER_DRAGGING;

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

            if (box.getPosX() >= m_positionX + 3.5f)
            {
                box.setPosX(m_positionX + 3.5f);
            }
            if (box.getPosX() <= m_positionX - 2.9f)
            {
                box.setPosX(m_positionX - 2.9f);
            }
        }
        if (ms.button_left_released)
        {
            releaseFocus();
            box.setActive(false);
            m_status_slider = SLIDER_RELEASED;
            setAction(true);
        }
    }
    else
    {
        if (m_status_slider == SLIDER_DRAGGING)
        {

            if (!requestFocus())
            {
                return;
            }

            if (mx >= 16.0f && box.getPosX() >= 16.0f)
            {
                mx = 16.0f;
                m_year = 2020;
            }

            if (mx <= m_positionX - 2.9f && box.getPosX() <= m_positionX - 2.9f)
            {
                mx = m_positionX - 2.9f;
                m_year = 1950;
            }

            box.setPosX(mx);

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

            if (box.getPosX() >= m_positionX + 3.5f)
            {
                box.setPosX(m_positionX + 3.5f);
            }
            if (box.getPosX() <= m_positionX - 2.9f)
            {
                box.setPosX(m_positionX - 2.9f);
            }
            if (!ms.dragging)
            {
                releaseFocus();
                box.setActive(false);
                m_status_slider = SLIDER_RELEASED;
                setAction(true);
            }
        }
    }

}

void Slider::draw()
{
    //Drawing our "line" and our clickable button
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

    //Drawing box
    if (m_uid == 9) //From
    {
        br.texture = "";
        graphics::drawRect(box.getPosX() + 0.1f, box.getPosY() + m_height + 0.3f, 0.2f, 0.5f, br);

        graphics::drawText(box.getPosX() - 0.25f, box.getPosY() + m_height, 0.3f, std::to_string((m_year)), br);
    }
    else //To
    {
        br.texture = "";
        graphics::drawRect(box.getPosX(), box.getPosY() + m_height + 0.6f, 0.2f, 0.5f, br);

        graphics::drawText(box.getPosX() - 0.25f, box.getPosY() + m_height + 0.3f, 0.3f, std::to_string((m_year)), br);
    }
    


}

bool Slider::contains(float x, float y) const
{
 
    if (m_uid == 9) //From
    {
       if (x >= box.getPosX() - 0.1f * 0.21f && x <= box.getPosX() + 0.1f * 0.21f ||
           y >= box.getPosY() + 4.05f + 0.3f - 0.1f * 0.5f && y <= box.getPosY() + 4.05f + 0.3f + 0.1f * 0.5f)
       {
          return true;
       }
          return false;
    }

    if (m_uid == 10)    //To
    {
        if (x >= box.getPosX() - 0.15f * 0.21f && x <= box.getPosX() + 0.1f * 0.21f ||
            y >= box.getPosY() + 4.05f + 0.6f - 0.1f * 0.5f && y <= box.getPosY() + 4.05f + 0.6f + 0.1f * 0.5f)
        {
            return true;
        }
        return false;
    }
    
}

void Slider::takeAction(const std::vector<Movie*>& movie_list)
{
    if (m_uid == 9) //From >= m_year
    {
        for (const auto& movie : movie_list)
        {
            if (std::stoi(movie->getDate()) >= m_year && std::stoi(movie->getDate()) <= (movie->getLastYearComparedfromTo()) && movie->getHasGenre())
            {
                movie->setDisabled(false);
                movie->setSkipped(false);
            }
            else
            {
                movie->setDisabled(true);
                movie->setSkipped(true);
            }
            movie->setLastYearComparedFrom(m_year);
        }

    }
    else if (m_uid == 10) // To
    {
        for (const auto& movie : movie_list)
        {
            if (std::stoi(movie->getDate()) <= m_year && (std::stoi(movie->getDate()) >= movie->getLastYearComparedFrom()) && !(movie->getLastYearComparedFrom() > m_year) && movie->getHasGenre())
            {
                movie->setDisabled(false);
                movie->setSkipped(false);
            }
            else
            {
                movie->setDisabled(true);
                movie->setSkipped(true);

            }
            movie->setLastYearComparedfromTo(m_year);
        }
    }
    

    setAction(false);
    setOperating(false);
    m_status_slider = SLIDER_IDLE;
}

void Slider::clearSlider()
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
}

Slider::Slider(float posX, float posY, const std::string_view text)
    : Widget(posX, posY), m_text{ text }
{
    clearSlider();
 
}
