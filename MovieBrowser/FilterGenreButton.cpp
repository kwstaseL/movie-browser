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
		movie->sethasFilteredGenre(false);
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
				movie->sethasFilteredGenre(true);
			}
		}
	}

	int movies_without_genre = 0;

	for (const auto& movie : movie_list)
	{
		if (movie->getGenreCount() != (s_scanned_genres.size()) && movie->isDisabled())
		{
			movies_without_genre++;
		}
	}

	if (movies_without_genre == movie_list.size())
	{
		for (const auto& movie : s_genreMap[m_button_text])
		{
			if (!movie->isSkipped())
			{
				movie->setDisabled(false);
			}
			movie->sethasFilteredGenre(true);
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
			//filter
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

void FilterGenreButton::draw()
{
	if (!m_visible)
	{
		return;
	}

	SETCOLOR(brush.fill_color, 0.2f * m_highlighted, 0.2f * m_highlighted, 0.2f * m_highlighted);
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
