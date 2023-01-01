#include "Button.h"


Button::Button(float posX, float posY, const std::string_view text)
	: Widget(posX, posY), m_button_text(text)
{
}

bool Button::contains(float mouse_x, float mouse_y) const
{
	return (mouse_x > m_positionX - m_Genrebutton_width / 2 && mouse_x < m_positionX + m_Genrebutton_width / 2 && mouse_y > m_positionY + m_height - m_Genrebutton_height / 2 && mouse_y < m_positionY+ m_height + m_Genrebutton_height / 2);
}

