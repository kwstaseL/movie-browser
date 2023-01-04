#include "FilterGenreButton.h"

//Input: a Movie
//Output: True or False
//Description: returns if a single movie, has filtered text (from textfield) and is in between the 2 years from the slider
bool FilterGenreButton::hasRequirements(const Movie* movie) const
{
	if (movie)
	{
		return std::stoi(movie->getDate()) <= movie->getLastYearComparedfromTo() && std::stoi(movie->getDate()) >= movie->getLastYearComparedFrom() && movie->getHasFilteredText();
	}
	return false;
}

/*
	Input: movie_list which contains all movies
	Description: filters all movies by the genre that is pressed or a combination of genres, 
	if a movie doesnt have that particular genre or genres, it gets disabled (it cant be drawn or updated)

*/
void FilterGenreButton::filterByGenre(const std::vector<Movie*>& movie_list)
{
	//If the genre map isn't created, create it 
	if (!isGenreMapCreated())
	{
		createGenreMap(movie_list);
	}

	//Inserting to the unordered set the button that was pressed
	s_scanned_genres.insert(m_button_text);

	hasAtLeastOneGenre = false;

	/*
		For every movie, we disable it and turn hasFilteredGenre to false, we also reset the Genre count which holds
		all the genres that the movie has
	*/
	for (const auto& movie : movie_list)
	{
		movie->setDisabled(true);
		movie->sethasFilteredGenre(false);
		movie->resetGenreCount();
	}

	//For all the genre buttons that where clicked
	for (const auto& genre : s_scanned_genres)
	{
		//For all movies inside the map with that specific genre
		for (const auto& movie : s_genreMap[genre])
		{
			if (!movie->isDisabled())
			{
				continue;
			}

			movie->AddGenreCount(1);	//Adding +1 since it has the current genre
		}
	}

	//For every movie
	for (const auto& movie : movie_list)
	{
		//If it has all genres that were pressed and it has requirements, then dont disable it, and set it that is it has all current genres
		//We use hasAtLeastOneGenre, just to check if there is a at least 1 movie that has all genres, if there isnt, we just filter by the last genre that was pressed
		if ((movie->getGenreCount() == (s_scanned_genres.size())) && hasRequirements(movie))
		{
			hasAtLeastOneGenre = true;
			movie->setDisabled(false);
			movie->sethasFilteredGenre(true);
		}
	}

	//Because no movie has all genres that were pressed, we just filter based on the last genre that was pressed
	if (!hasAtLeastOneGenre)
	{
		for (const auto& movie : s_genreMap[m_button_text])
		{
			if (hasRequirements(movie))
			{
				movie->setDisabled(false);
				movie->sethasFilteredGenre(true);
			}
		}
	}
	releaseFocus();
}


//Creates the genreMap
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

void FilterGenreButton::clear()
{
	s_scanned_genres.clear();
}

void FilterGenreButton::takeAction(const std::vector<Movie*>& movie_list)
{
	filterByGenre(movie_list);
}


//Updating all filter genre buttons
void FilterGenreButton::update()
{
	m_height += 0.01f * graphics::getDeltaTime();

	if (m_height > 2.0f)
	{
		m_height = 2.0f;
	}

	if (!m_visible)
	{
		//reset back to position animation
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
			setOperating(false);
		}
	}
	else
	{
		m_highlighted = false;
	}
}


//Drawing of all filter genre buttons
void FilterGenreButton::draw()
{
	if (!m_visible)
	{
		return;
	}

	SETCOLOR(brush.fill_color, 0.8f * m_highlighted, 0.8f * m_highlighted, 0.8f * m_highlighted);
	brush.outline_opacity = 1.0f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width + 0.1, m_Genrebutton_height + 0.1, brush);

	brush.fill_opacity = 1.0f;
	SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(m_positionX - 0.45f, m_positionY + 0.125f + m_height, 0.4f, m_button_text, brush);

	SETCOLOR(brush.fill_color, 0.0f, 0.0f, 0.0f);

	//Draw our button
	brush.texture = "";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.5f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width, m_Genrebutton_height, brush);
}

FilterGenreButton::FilterGenreButton(float posX, float posY, const std::string_view text)
	: Button(posX, posY, text)
{
}