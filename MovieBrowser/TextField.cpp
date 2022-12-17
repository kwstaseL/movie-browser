#include "TextField.h"

void TextField::draw()
{
	if (!m_visible)
	{
		return;
	}

	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.5f, 0.5f, 0.5f);
	graphics::drawRect(m_positionX, m_positionY + m_height, 4.0f, 0.5f, br);

	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	graphics::drawText(m_positionX - 2.0f, m_positionY + 0.5f, 0.3f, m_text, br);
}

void TextField::update()
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

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);


}

void TextField::takeAction(const std::vector<Movie*>& movie_list)
{
}

bool TextField::contains(float x, float y) const 
{
	return FunctionsConst::distance(x, y, m_positionX, m_positionY);
}

void TextField::deleteText() {

}

TextField::TextField(float posX, float posY, const std::string_view text)
	:Widget(posX, posY)
{}
