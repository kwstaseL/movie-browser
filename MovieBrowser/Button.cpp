#include "Button.h"
#include <iostream>


Button::Button(float posX, float posY, const std::string_view text)
	: Widget(posX, posY), m_button_text(text)
{
}


bool Button::contains(float x, float y) const
{
	return FunctionsConst::distance(x, y, m_positionX, m_positionY+m_height) < m_Genrebutton_height * m_Genrebutton_width * 0.14f;

}


