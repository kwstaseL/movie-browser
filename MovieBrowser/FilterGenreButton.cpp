#include "FilterGenreButton.h"

void FilterGenreButton::filterByGenre(const std::vector<Movie*>& movie_list)
{
	if (!isGenreMapCreated())
	{
		createGenreMap(movie_list);
	}

	s_scanned_genres.insert(m_button_text);

	for (const auto& movie : movie_list)
	{
		movie->setDisabled(true);
		movie->setHasGenre(false);
		movie->resetGenreCount();
	}

	for (const auto& genre : s_scanned_genres)
	{
		for (const auto& movie : s_genreMap[genre])
		{
			movie->AddGenreCount(1);

			if ((movie->getGenreCount() == (s_scanned_genres.size())) && !movie->isSkipped() && movie->isDisabled())
			{
				movie->setDisabled(false);
				movie->setHasGenre(true);
			}
		}
	}

	int movies_without = 0;

	for (const auto& movie : movie_list)
	{
		if (movie->getGenreCount() != (s_scanned_genres.size()) && movie->isDisabled())
		{
			movies_without++;
		}
	}

	if (movies_without == movie_list.size())
	{
		for (const auto& movie : s_genreMap[m_button_text])
		{
			
			movie->setDisabled(false);
			movie->setHasGenre(true);

			
		}
	}
}

void FilterGenreButton::createGenreMap(const std::vector<Movie*>& movie_list)
{
	for (const auto& movie : movie_list)
	{
		for (const auto& genre : movie->genres)
		{
			s_genreMap[genre].insert(movie);
		}
	}
	setGenreMapCreated(true);
}

void FilterGenreButton::takeAction(const std::vector<Movie*>& movie_list)
{
	filterByGenre(movie_list);
}

void FilterGenreButton::update()
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

	float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
	float my{ graphics::windowToCanvasY(ms.cur_pos_y) };

	if (contains(mx, my))
	{
		m_button_state = BUTTON_HIGHLIGHTED;

		m_highlighted = true;

		if (ms.button_left_pressed)	//Button is pressed here
		{
			if (!requestFocus())
			{
				return;
			}

			m_button_state = BUTTON_PRESSED;
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("button.wav"), 0.5f);
			setAction(true);
		}
		if (ms.button_left_released) //Button was pressed and now is released
		{
			//filter
			m_button_state = BUTTON_IDLE;
			setAction(false);
			releaseFocus();
			setOperating(false);
		}
	}
	else
	{
		m_highlighted = false;
	}
}

void FilterGenreButton::draw()
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
	graphics::drawText(m_positionX - 0.45f, m_positionY + 0.125f + m_height, 0.4f, m_button_text, brush);

	SETCOLOR(brush.fill_color, 0.0f, 0.0f, 0.0f);

	//Draw our button
	brush.texture = "";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.2f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width, m_Genrebutton_height, brush);
}

FilterGenreButton::FilterGenreButton(float posX, float posY, const std::string_view text)
   : Button(posX, posY, text)
{
}
