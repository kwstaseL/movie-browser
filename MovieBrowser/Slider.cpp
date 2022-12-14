#include "Slider.h"
#include <iostream>

//DONE

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

        if (ms.dragging && box.isActive())
        {

            if (mx >= 16.0f && box.getPosX() >= 16.0f)
            {
                mx = 16.0f;
            }

            if (mx <= m_positionX - 2.9f && box.getPosX() <= m_positionX - 2.9f)
            {
                mx = m_positionX - 2.9f;
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
            box.setActive(false);
            m_status_slider = SLIDER_RELEASED;
            setAction(true);
        }
    }
    else
    {
        if (m_status_slider == SLIDER_DRAGGING)
        {

            if (mx >= 16.0f && box.getPosX() >= 16.0f)
            {
                mx = 16.0f;
            }

            if (mx <= m_positionX - 2.9f && box.getPosX() <= m_positionX - 2.9f)
            {
                mx = m_positionX - 2.9f;
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

    graphics::drawText(box.getPosX() - 0.25f, box.getPosY() + m_height, 0.3f, std::to_string((m_year)), br);


    brush.texture = "";
    brush.fill_opacity = 0.1;
    brush.outline_opacity = .5f;
    graphics::drawRect(m_positionX, m_positionY + m_height, 7.0f, .0001f, brush);

    //Drawing box
    br.texture = "";
    graphics::drawRect(box.getPosX() + 0.1f, box.getPosY() + m_height + 0.6, 0.2f, 0.5f, br);

}

bool Slider::contains(float x, float y) const
{
    if (x >= box.getPosX() - 0.1f * 0.2f && x <= box.getPosX() + 0.1f * 0.2f ||
        y >= box.getPosY() + 4.0f + 0.6 - 0.1f * 0.5f && y <= box.getPosY() + 4.0f + 0.6f + 0.1f * 0.5f)
    {
        return true;
    }
    return false;
}

void Slider::takeAction(const std::vector<Movie*>& movie_list)
{

    for (const auto& movie : movie_list)
    {
        
            if (std::stoi(movie->getDate()) >= (m_year))
            {
                movie->setDisabled(true);
                movie->setSkipped(true);
            }
            else
            {
                movie->setDisabled(false);
                movie->setSkipped(false);

            }
        }

    setAction(false);
    setOperating(false);
    m_status_slider = SLIDER_IDLE;
}

Slider::Slider(float posX, float posY, const std::string_view text)
    : Widget(posX, posY), m_text{ text }
{

    box.setPosX(m_positionX - 2.9f);
    box.setPosY(m_positionY - 0.56f);
    //Create button here

}

