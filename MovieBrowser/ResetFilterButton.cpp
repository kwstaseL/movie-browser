#include "ResetFilterButton.h"


void ResetFilterButton::resetFilter(const std::vector<Movie*>& movie_list) const
{
	for (const auto& movie : movie_list)
	{
		movie->setDisabled(false);

		movie->sethasFilteredGenre(true);
		movie->sethasFilteredText(true);

		movie->setLastYearComparedFrom(1950);
		movie->setLastYearComparedfromTo(2020);
		s_scanned_genres.clear();
	}
}

void ResetFilterButton::takeAction(const std::vector<Movie*>& movie_list)
{
	resetFilter(movie_list);
}

void ResetFilterButton::update()
{
	m_height += 0.01f * graphics::getDeltaTime();

	if (m_height > 2.0f)
	{
		m_height = 2.0f;
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

	if (contains(mouse_X, mouse_Y))
	{
		m_button_state = button_state_t::BUTTON_HIGHLIGHTED;

		m_highlighted = true;

		if (ms.button_left_pressed)	//Button is pressed here
		{
			if (!requestFocus())
			{
				return;
			}

			m_button_state = button_state_t::BUTTON_PRESSED;
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("button.wav"), 0.5f);
			setActionTriggered(true);
		}
		if (ms.button_left_released) //Button was pressed and now is released
		{
			m_button_state = button_state_t::BUTTON_IDLE;
			setActionTriggered(false);
			releaseFocus();
			setOperating(false);
		}
	}
	else
	{
		m_highlighted = false;
	}
}

void ResetFilterButton::draw()
{
	if (!m_visible)
	{
		return;
	}
	float highlight = 0.2f * m_highlighted;

	SETCOLOR(brush.fill_color, highlight, highlight, highlight);
	brush.outline_opacity = 0.0f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width + 0.1, m_Genrebutton_height + 0.1, brush);

	brush.fill_opacity = 1.0f;
	SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(m_positionX - 0.75f, m_positionY + 0.125f + m_height, 0.4f, m_button_text, brush);

	SETCOLOR(brush.fill_color, 0.6f, 0.1f, 0.2f);

	//Draw our button
	brush.texture = "";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.2f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width, m_Genrebutton_height, brush);
}

ResetFilterButton::ResetFilterButton(float posX, float posY, const std::string_view text)
	: Button(posX, posY,text)
{
}
