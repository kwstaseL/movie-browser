#include "Button.h"


Button::Button(const std::string_view text)
	:m_button_text{ text }
{}



bool Button::contains(float mouse_x, float mouse_y) const
{
	return (mouse_x > m_positionX - m_button_width / 2 && mouse_x < m_positionX + m_button_width / 2 
		&& mouse_y > m_positionY + m_height - m_button_height / 2 && mouse_y < m_positionY + m_height + m_button_height / 2);
}

