#include "Button.h"

//COMPLETED

//Constructs a new button
// @param posX: the x coordinate of the button's position
// @param posY: the y coordinate of the button's position
// @param text: the text displayed on the button

Button::Button(float posX, float posY, const std::string_view text)
	: Widget(posX, posY), m_button_text{text}
{
}

// Checks if the mouse is within the coordinates of the button
// m_positionX,m_positionY is the Dock's position on the canvas
// @param mouse_x: the x coordinate of the mouse
// @param mouse_y: the y coordinate of the mouse
// @return true if the mouse is within the button's coordinates, false otherwise
bool Button::contains(float mouse_x, float mouse_y) const
{
	return (mouse_x > m_positionX - m_Genrebutton_width / 2 && mouse_x < m_positionX + m_Genrebutton_width / 2 
		&& mouse_y > m_positionY + m_height - m_Genrebutton_height / 2 && mouse_y < m_positionY + m_height + m_Genrebutton_height / 2);
}
