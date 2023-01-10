#include "TextField.h"
#include <algorithm>
#include <iostream>

/*
		Function which takes as input a Movie pointer, and checks if this particular movie
		has the filtered genre (if any filter button was pressed) ,
		and if it has the 2 years we filter with the slider

		It helps us filter movies, synchronizing all widgets
		Returns true if movie has a filtered genre("Action","Drama" etc..) and is between the 2 years
		Returns false otherwise
*/

bool TextField::hasRequirements(const Movie* movie) const
{
	if (movie)
	{
		for (const auto& filter : filterToBeChecked)
		{
			if (movie->state_info.getWidgetState(filter) != WidgetEnums::WidgetFilterState::ENABLED)
			{
				return false;
			}
		}
		return std::stoi(movie->getDate()) <= movie->state_info.getLastFilterToYear() && std::stoi(movie->getDate()) >= movie->state_info.getLastFilterFromYear();
	}
}

void TextField::draw()
{
	/*
	*	Draws our textfield, only if the textfield is visible (dock is down)
	*/

	if (!m_visible)
	{
		return;
	}

	graphics::Brush br;

	// Set the color of the brush based on whether the TextField is highlighted or not

	SETCOLOR(br.fill_color, 0.5f * m_highlighted, 0.5f * m_highlighted, 0.5f * m_highlighted);
	brush.outline_opacity = 1.0f;

	// Drawing the TextField
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Textfield_width, m_Textfield_height, br);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	// If the TextField is highlighted and there is no text in it, draw some text inside the TextField

	if (!textInvisible && characters.empty())
	{
		graphics::drawText(m_positionX - 0.8f, m_positionY + m_height + 0.1f, 0.3f, m_text, br);
	}

}

void TextField::update()
{

	// If the TextField is not visible, reset its height and highlighting
	if (!m_visible)
	{
		m_highlighted = false;
		return;
	}

	// Getting mouse state and converting pos_x,pos_y to canvas units
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);


	// If our mouse contains textfields coordinates
	if (contains(mouse_X, mouse_Y))
	{
		//If button is pressed, hide the text "Search Movie/Director", and highlight the box
		if (ms.button_left_pressed)
		{
			textInvisible = true;
			m_highlighted = true;
		}
	}
	else
	{
		// If the mouse is not within the bounds of the text field, reset the highlighting

		if (ms.button_left_pressed)
		{
			m_highlighted = false;
		}
	}

	// If button is highlighted (user has pressed the button)
	if (m_highlighted)
	{
		char ascii = 0;

		//Looping for each available keystate (excluding {BACKSPACE,SPACE})
		//to see if they are being pressed
		for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_Z; i++)
		{
			// If a key is being pressed and we are ready to type again
			if (graphics::getKeyState((graphics::scancode_t)i))
			{
				if (!m_typed)
				{
					// Convert the key to ASCII and add it to the text field
					ascii = (char)(i + 93);

					m_timer = 0;	//Reset Timer
					characters.push_back(ascii);	//Pushing back to the deque the character the user pressed
					m_typed = true;
					setActionTriggered(true);	// Since user typed a key trigger a signal so takeAction is called and action is taken.

					if (isFull)	//If the text field is full, store the first character in a stack and remove it from the text field
					{
						outofsight_words.push(characters[0]);
						characters.erase(characters.begin());	
						extra_words++;	//Variable to count how many extra words are kept in the stack
					}
				}
			}
			if (graphics::getKeyState((graphics::SCANCODE_SPACE)))	//Check if the SPACE key is being pressed
			{
				if (!m_typed)	//Add a space to the text field
				{
					m_timer = 0;
					characters.push_back(' ');

					m_typed = true;
					setActionTriggered(true);

					//If the text field is full, store the first character in a stack and remove it from the text field

					if (isFull)
					{
						outofsight_words.push(characters[0]);
						characters.erase(characters.begin());
						extra_words++;
					}
				}
			}
			if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE))	        //Check if the BACKSPACE key is being pressed
			{
				if (!characters.empty() && (!m_typed))	//If I can type and the characters is not empty
				{
					if (isFull)	// If the textfield is full
					{
						if (!outofsight_words.empty())
						{
							characters.push_front(outofsight_words.top());	//Starting putting back to the beginning of the textfield the words of the stack
							extra_words--;
							outofsight_words.pop();
						}
					}

					if (!characters.empty())
					{
						characters.pop_back();
					}

					m_typed = true;
					m_timer = 0;

				}
				setActionTriggered(true);
			}
		}
		m_timer++;	//Increments the timer

		if (m_timer > 8)	//If the timer surpasses a default value of 8
			m_typed = false;	//Alerts that the user can now type again

		if (characters.size() + extra_words >= 25)	//If characters surpasses 25, the textfield is full
		{
			isFull = true;
		}
		else
		{
			isFull = false;
			extra_words = 0;
		}
	}

	if (!characters.empty())	//If the characters is not empty, draw the string
	{
		std::string textfield_string(characters.begin(), characters.end());
		graphics::drawText(m_positionX - 1.9f, m_positionY + m_height + 0.1f, 0.3f, textfield_string, brush);
	}
	else //else just draw the "Search Movie" text
	{
		graphics::drawText(m_positionX - 0.8f, m_positionY + m_height + 0.1f, 0.3f, m_text, brush);
	}
}

/*
* Takes a list of movies and performs some actions on them (search by title).
* @param movie_list The list of movies to perform actions on.
*/
void TextField::takeAction(const std::vector<Movie*>& movie_list)
{
	search(movie_list);
}

/*
* Searches for movies by title using the given list of movies.
* If the current string in the textfield is a substring of a movie's title, the movie is marked as enabled and has the text filter applied.
* If the current string in the textfield is not a substring of a movie's title, the movie is marked as disabled and does not have the text filter applied.
* If the key state is Backspace or the character string is empty, all movies that have the current title are marked as enabled and have the text filter applied.
* @param movie_list The list of movies to search through.
*/
void TextField::search(const std::vector<Movie*>& movie_list)
{
	if (!requestFocus())	//If someone else is operating currently, return
	{
		return;
	}

	std::string string(characters.begin(), characters.end());	//Making a string out of the deque characters

	for (const auto& movie : movie_list)
	{
		std::string movie_name = movie->getName();
		std::string movie_director = movie->getDir();  // Add this line to get the director

		std::transform(movie_name.begin(), movie_name.end(), movie_name.begin(), ::tolower);
		std::transform(movie_director.begin(), movie_director.end(), movie_director.begin(), ::tolower); // Add this line to change director to lower case

		//If keystate was BackSpace or the character is empty, find all the movies that have the current string on their title or director
		if ((movie_name.find(string) != std::string::npos || movie_director.find(string) != std::string::npos)
			&& (graphics::getKeyState(graphics::SCANCODE_BACKSPACE) || characters.empty()))
		{
			if (hasRequirements(movie))
			{
				movie->state_info.setDisabled(false);
				movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::ENABLED);
			}
		}

		//If movie title or director doesn't have the current textfield title anywhere in their title, disable it, and setTextFilterApplied = False to alert all the other widgets
		if (movie_name.find(string) == std::string::npos && movie_director.find(string) == std::string::npos)
		{
			movie->state_info.setDisabled(true);
			movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::DISABLED);
		}
		else
		{
			movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::ENABLED);
		}
	}

	setActionTriggered(false);
	m_operating = false;
	releaseFocus();
}

/*
* Clears the characters in the textfield.
*/
void TextField::clear()
{
	characters.clear();
	extra_words = 0;
	textInvisible = false;
}

/*
	* Check if the mouse is inside the bounds of the text field (based on its height and width).
	* @param x The x coordinate of the mouse.
	* @param y The y coordinate of the mouse.
	* @return true if the mouse is inside the bounds of the text field, false otherwise.
*/
bool TextField::contains(float mouse_x, float mouse_y) const
{

	return (mouse_x > m_positionX - m_Textfield_width / 2 && mouse_x < m_positionX + m_Textfield_width / 2 && mouse_y > m_positionY + m_height - m_Textfield_height / 2 && mouse_y < m_positionY + m_height + m_Textfield_height / 2);

}

TextField::TextField(float posX, float posY, const std::string_view text)
	: Widget(posX, posY), m_text{ text }
{
	filterToBeChecked.push_back(WidgetEnums::WidgetFilters::TitleFilter);
	filterToBeChecked.push_back(WidgetEnums::WidgetFilters::GenreFilter);
}