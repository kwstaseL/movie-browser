#include "Button.h"


Button::Button(float posX, float posY, const std::string_view text)
	: Widget(posX, posY), m_button_text(text)
{
}

bool Button::contains(float x, float y) const
{
	return FunctionsConst::distance(x, y, m_positionX, m_positionY + m_height) < m_Genrebutton_height/10.0f * m_Genrebutton_width + 0.25f;

}

