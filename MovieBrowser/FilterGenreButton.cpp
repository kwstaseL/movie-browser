#include "FilterGenreButton.h"

//COMPLETED

/*
	Checks if the given movie meets the requirements for filtering (checks if is already filtered by other widgets),
	used to sychronize all filters with all widgets that can filter, together.
	@param movie: a pointer to the movie to be checked
	@return true if the movie meets the requirements, false otherwise
*/
bool FilterGenreButton::hasRequirements(const Movie* movie) const
{
	if (movie)
	{
		return std::stoi(movie->getDate()) <= movie->state_info.getLastFilterToYear()
			&& std::stoi(movie->getDate()) >= movie->state_info.getLastFilterFromYear() 
			&& movie->state_info.getWidgetState(WidgetEnums::WidgetKeys::TitleFilter) == WidgetEnums::WidgetFilterState::ENABLED;
	}

	return false;
}

// Filters all movies by genre
// @param movie_list: a vector of all the movies to be filtered
void FilterGenreButton::filterByGenre(const std::vector<Movie*>& movie_list)
{
	//If the genre map isn't created, create it 
	if (!isGenreMapCreated())
	{
		createGenreMap(movie_list);
	}

	//Inserting to the unordered set the button (text) that was pressed
	s_scanned_genres.insert(m_button_text);

	atLeastOneMovieHasGenres = false;
	/*
		For every movie, we disable it and turn genre filter state to false, we also reset the Genre count which holds
		all the current genres that are pressed by the user the movie has
	*/
	for (const auto& movie : movie_list)
	{
		movie->state_info.setDisabled(true);
		movie->state_info.updateWidgetState(WidgetEnums::WidgetKeys::GenreFilter, WidgetEnums::WidgetFilterState::DISABLED);
		movie->state_info.resetGenreCount();
	}

	//For all the genre buttons that where clicked
	for (const auto& genre : s_scanned_genres)
	{
		//For all movies inside the map with that specific genre
		for (const auto& movie : s_genreMap[genre])
		{
			if (!movie->state_info.isDisabled())
			{
				continue;
			}
			movie->state_info.AddGenreCount(1);	//Adding +1 since it has the current genre
		}
	}

	//For every movie
	for (const auto& movie : movie_list)
	{
		//If it has all genres that were pressed and it has requirements, then dont disable it, and set it that is it has all current genres
		//We use hasAtLeastOneGenre, just to check if there is a at least 1 movie that has all genres, if there isn't, we just filter by the last genre that was pressed
		if ((movie->state_info.getGenreCount() == (s_scanned_genres.size())) && hasRequirements(movie))
		{
			atLeastOneMovieHasGenres = true;
			movie->state_info.setDisabled(false);
			movie->state_info.updateWidgetState(WidgetEnums::WidgetKeys::GenreFilter, WidgetEnums::WidgetFilterState::ENABLED);
		}
	}

	//Because no movie has all genres that were pressed, we just filter based on the last genre that was pressed
	if (!atLeastOneMovieHasGenres)
	{
		for (const auto& movie : s_genreMap[m_button_text])
		{
			if (hasRequirements(movie))
			{
				movie->state_info.setDisabled(false);
				movie->state_info.updateWidgetState(WidgetEnums::WidgetKeys::GenreFilter, WidgetEnums::WidgetFilterState::ENABLED);
			}
		}
	}
	releaseFocus();	//Releasing focus since operation is done
}


/* Creates the genre map
@param movie_list: a vector of all the movies to be included in the genre map
The genre map is a mapping from genre names to unordered sets of movies with that genre. It is used to quickly filter movies by genre.
*/
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

// Resets the state of the button
void FilterGenreButton::clear()
{
	s_scanned_genres.clear();
}

// Performs the filtering action when the button is pressed
// @param movie_list: a vector of all the movies to be filtered
void FilterGenreButton::takeAction(const std::vector<Movie*>& movie_list)
{
	filterByGenre(movie_list);
}

//Updating all filter genre buttons
void FilterGenreButton::update()
{

	if (!m_visible)	//If the widget is invisible , return
	{
		return;
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	//Converting mouse_x,mouse_y to canvas units
	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

	//Checking if our mouse is in bounds of buttons coordinates
	if (contains(mouse_X, mouse_Y))
	{
		m_button_state = button_state_t::BUTTON_HIGHLIGHTED;

		m_highlighted = true;

		if (ms.button_left_pressed)	//Mouse is pressed
		{
			if (!requestFocus())	//If someone else is operating, return
			{
				return;
			}

			m_button_state = button_state_t::BUTTON_PRESSED;
			graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("button.wav"), 0.5f);
			setActionTriggered(true);	//Alert that the button was clicked
		}
		if (ms.button_left_released) //Button was pressed and now is released
		{
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


//Drawing our filter genre button
void FilterGenreButton::draw()
{
	if (!m_visible)	//If the widget is invisible , return
	{
		return;
	}

	//Drawing highlight
	SETCOLOR(brush.fill_color, 0.8f * m_highlighted, 0.8f * m_highlighted, 0.8f * m_highlighted);
	brush.outline_opacity = 1.0f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width + 0.1, m_Genrebutton_height + 0.1, brush);

	//Drawing m_button_text which represents the buttons name ("Action","Drama"..)
	brush.fill_opacity = 1.0f;
	SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(m_positionX - 0.45f, m_positionY + 0.125f + m_height, 0.4f, m_button_text, brush);

	SETCOLOR(brush.fill_color, 0.0f, 0.0f, 0.0f);

	//Drawing our button
	brush.texture = "";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.5f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Genrebutton_width, m_Genrebutton_height, brush);
}


/* Constructs a new filter genre button
@param posX: the x coordinate of the button's position
@param posY: the y coordinate of the button's position
@param text: the text displayed on the button
*/
FilterGenreButton::FilterGenreButton(float posX, float posY, const std::string_view text)
	: Button(posX, posY, text)
{
}