#include "Slider.h"

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

    int temp{ ClickableBox.getPosX() };

    if (contains(mx, my))
    {
        ClickableBox.setActive(true);

        if (ms.dragging && ClickableBox.isActive())
        {

            if (mx >= 16.0f && ClickableBox.getPosX() >= 16.0f)
            {
                mx = 16.0f;
            }
            
            if (mx <= m_positionX - 2.9f && ClickableBox.getPosX() <= m_positionX - 2.9f)
            {
                mx = m_positionX - 2.9f;
            }

            ClickableBox.setPosX(mx);

            m_status_slider = SLIDER_DRAGGING;

            if (temp < ClickableBox.getPosX())
            {
                m_year += 10;
            }
            else if (temp > ClickableBox.getPosX())
            {
                m_year -= 10;
            }
            else {

                m_year += 0;
            }

            if (ClickableBox.getPosX() >= m_positionX + 3.5f)
            {
                ClickableBox.setPosX(m_positionX + 3.5f);
            }
            if (ClickableBox.getPosX() <= m_positionX - 2.9f)
            {
                ClickableBox.setPosX(m_positionX - 2.9f);
            }
        }
        if (ms.button_left_released)
        {
            ClickableBox.setActive(false);
            m_status_slider = SLIDER_RELEASED;
            setAction(true);
        }
    }
    else
    {
        if (m_status_slider == SLIDER_DRAGGING)
        {

            if (mx >= 16.0f && ClickableBox.getPosX() >= 16.0f)
            {
                mx = 16.0f;
            }

            if (mx <= m_positionX - 2.9f && ClickableBox.getPosX() <= m_positionX - 2.9f)
            {
                mx = m_positionX - 2.9f;
            }

            ClickableBox.setPosX(mx);

            if (temp < ClickableBox.getPosX())
            {
                m_year +=  10;
            }
            else if (temp > ClickableBox.getPosX())
            {
                m_year -= 10;
            }
            else {

                m_year += 0;
            }

            if (ClickableBox.getPosX() >= m_positionX + 3.5f)
            {
                ClickableBox.setPosX(m_positionX + 3.5f);
            }
            if (ClickableBox.getPosX() <= m_positionX - 2.9f)
            {
                ClickableBox.setPosX(m_positionX - 2.9f);
            }
            if (!ms.dragging)
            {
                ClickableBox.setActive(false);
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
    graphics::drawText(m_positionX - 4.5f, m_positionY + m_height + 0.115f,0.3f, m_text, br);

    graphics::drawText(ClickableBox.getPosX()-0.25f,ClickableBox.getPosY()+m_height, 0.3f, std::to_string((m_year)), br);


    brush.texture = "";
    brush.fill_opacity = 0.1;
    brush.outline_opacity = .5f;
    graphics::drawRect(m_positionX, m_positionY + m_height, 7.0f, .0001f, brush);

    //Drawing box
    br.texture = "";
    graphics::drawRect(ClickableBox.getPosX()+0.1f, ClickableBox.getPosY() + m_height +0.6, 0.2f, 0.5f, br);

}

bool Slider::contains(float x, float y) const
{
    if (x >= ClickableBox.getPosX() - 0.1f * 0.2f && x <= ClickableBox.getPosX() + 0.1f * 0.2f ||
        y >= ClickableBox.getPosY() + 4.0f + 0.6 - 0.1f * 0.5f && y <= ClickableBox.getPosY() + 4.0f + 0.6f + 0.1f * 0.5f)
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

    ClickableBox.setPosX(m_positionX-2.9f);
    ClickableBox.setPosY(m_positionY- 0.56f);
    //Create button here

}

void Slider::resetSlider()
{
   ClickableBox.setPosX(m_positionX - 2.9f);
   m_year = 1950;
}

