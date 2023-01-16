#include "TextField.h"
#include <algorithm>



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

// Continuously draws our textfield.
void TextField::draw()
{
	//If the textfield is invisible return.
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

// Continously updates our TextField.

void TextField::update()
{

	//If the textfield is invisible , reset the highlighting and return.
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
		//If button is pressed, hide the text "Search Movie/Dir/Prot", and highlight the box
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
					m_action = true;	//Takes the action (filtering) since we need to find the movies with this parcticular string that the user gave.

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
				if (!m_typed)	//Add a space to the deque which holds all the characters
				{
					m_timer = 0;
					characters.push_back(' ');

					m_typed = true;
					m_action = true; //Takes the action (filtering) since we need to find the movies with this parcticular string

					//If the text field is full, store the first character in a stack and remove it from the text field, also we keep how many extra words are
					// inserted in tto the stack.
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
							outofsight_words.pop();	//Removing the world we have already inserted to the front of the word from the stack.
						}
					}

					if (!characters.empty())
					{
						characters.pop_back();	//Removing from the end of the characters deque, since the keyState was BACKSPACE
					}

					m_typed = true; //set the flag to true since the user has typed
					m_timer = 0; //Resetting the timer 

				}
				m_action = true;	//Takes the action (filtering) since we need to find the movies with this parcticular string where the character was removed from the end
			}
		}
		m_timer++;	//Increments the timer

		if (m_timer > 9)	//If the timer surpasses a default value of 8
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
	else //else just draw the "Search Movie/Director/Protagonist" text
	{
		graphics::drawText(m_positionX - 0.8f, m_positionY + m_height + 0.1f, 0.3f, m_text, brush);
	}
}

/*
* Takes a list of movies and performs some actions on them (search by title/dir/protagonist).
* \param movie_list The list of movies to perform actions on.
*/
void TextField::takeAction(const std::vector<Movie*>& movie_list)
{
	if (m_textfield_filter == TextFieldFiltering::FilterBy::TITLE_PROTAGONIST_DIRECTOR)
	{
		searchByTitleProtDir(movie_list);
	}
}

/*
* Searches for movies by title/director/protagonist using the given list of movies.
* \param movie_list The list of movies to search through.
*/
void TextField::searchByTitleProtDir(const std::vector<Movie*>& movie_list)
{
	if (!requestFocus())   //If someone else is operating currently, return
	{
		return;
	}

	std::string search_string(characters.begin(), characters.end());   //Making a string out of the deque characters

	//For each movie, we check whether this movie is referred given a search_string, based on either each protaginsts, director or title.
	for (const auto& movie : movie_list)
	{
		std::string movie_name = movie->getName();	//Getting the name of the movie we have to create a new string, since we do not want to modify the original when performing lowercase.
		std::string movie_director = movie->getDir();	//Getting the director of the movie we have to create a new string, since we do not want to modify the original when performing lowercase.

		std::transform(movie_name.begin(), movie_name.end(), movie_name.begin(), ::tolower);	// This process,takes the name of the movie and converts it to lowercase
		std::transform(movie_director.begin(), movie_director.end(), movie_director.begin(), ::tolower); // This process,takes the the name of the director and converts it to lowercase

		//Checking if the searching word that was given is referring to a protagonist.
		bool hasProtagonist{ false };

		//We are using find() method to see if the inputted string is present in the dir/title of protagonist name, if it isn't it returns the std::string::npos
		for (const auto& protagonist : movie->m_protagonists)
		{
			std::string protagonist_name = protagonist;
			std::transform(protagonist_name.begin(), protagonist_name.end(), protagonist_name.begin(), ::tolower);
			if (protagonist_name.find(search_string) != std::string::npos)	//If the textfield finds a protagonist name for a movie, then set hasProtagonist ot true
			{
				hasProtagonist = true;
				break;
			}

		}

		//If keystate was BackSpace or the character is empty, it finds
		// all the movies that have the current string on their title, director or protagonist (with the backspace applied or if the character is empty (empty string)))
		// and have all other widgets applied

		if ((movie_name.find(search_string) != std::string::npos || movie_director.find(search_string) != std::string::npos || hasProtagonist)
			&& ((graphics::getKeyState(graphics::SCANCODE_BACKSPACE) || characters.empty())))
		{
			if (hasRequirements(movie))
			{
				movie->state_info.setDisabled(false);
				movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::ENABLED);
				continue;	//If this movie has either title,director,protagonist continue with the next movie
			}
		}

		//If movie title,director or protagonist doesn't have the current textfield title (find() returned npos) anywhere in their name, disable it, and also set the filterstate to be disabled for this movie.
		if (movie_name.find(search_string) == std::string::npos && movie_director.find(search_string) == std::string::npos && !hasProtagonist)
		{
			movie->state_info.setDisabled(true);
			movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::DISABLED);
		}
		else
		{
			movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::ENABLED);
		}
	}
	m_action = false;
	m_operating = false;
	releaseFocus();
}

// Clears all variables of the textfield
void TextField::clear()
{
	characters.clear();
	extra_words = 0;
	textInvisible = false;
	m_timer = -1;
}

/*
* Check if the mouse is inside the coordinates of the text field.
* \param x The x coordinate of the mouse.
* \param y The y coordinate of the mouse.
* \return true if the mouse is in the coordinates of textfield
*/
bool TextField::contains(float mouse_x, float mouse_y) const
{

	return (mouse_x > m_positionX - m_Textfield_width / 2 && mouse_x < m_positionX + m_Textfield_width / 2 
		&& mouse_y > m_positionY + m_height - m_Textfield_height / 2 && mouse_y < m_positionY + m_height + m_Textfield_height / 2);

}

TextField::TextField(float posX, float posY, const std::string_view text, const TextFieldFiltering::FilterBy& filter)
	: Widget(posX, posY), m_text{ text },m_textfield_filter{filter}
{
	//Inserting all the widgets textfield must check before filtering the movies.
	filterToBeChecked.push_back(WidgetEnums::WidgetFilters::TitleFilter);
	filterToBeChecked.push_back(WidgetEnums::WidgetFilters::GenreFilter);
}