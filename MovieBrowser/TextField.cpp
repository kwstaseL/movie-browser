#include "TextField.h"
#include <algorithm>


void TextField::draw()
{
	if (!m_visible)
	{
		return;
	}

	graphics::Brush br;

	// Set the color of the brush based on whether the TextField is highlighted or not
	const float HIGHLIGHT_COLOR_FACTOR = 0.5f;
	SETCOLOR(br.fill_color, HIGHLIGHT_COLOR_FACTOR * m_highlighted, HIGHLIGHT_COLOR_FACTOR * m_highlighted, HIGHLIGHT_COLOR_FACTOR * m_highlighted);
	brush.outline_opacity = 1.0f;

	// Drawing the TextField
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Textfield_width, m_Textfield_height, br);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	// If the TextField is highlighted and there is no text in it, draw some text inside the TextField
	if (!isTextInvisible && m_characters.empty())
	{
		const float TEXTFIELD_TEXT_OFFSET_X = -0.8f;
		const float TEXTFIELD_TEXT_OFFSET_Y = 0.1f;
		graphics::drawText(m_positionX + TEXTFIELD_TEXT_OFFSET_X, m_positionY + m_height + TEXTFIELD_TEXT_OFFSET_Y, 0.3f, m_text, br);
	}

}

void TextField::update()
{

	if (!m_visible)
	{
		m_highlighted = false;
		return;
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	mouse_X = graphics::windowToCanvasX(ms.cur_pos_x);
	mouse_Y = graphics::windowToCanvasY(ms.cur_pos_y);

	bool mouseOverField = contains(mouse_X, mouse_Y);
	if (mouseOverField)
	{
		//If button is pressed, hide the text "Search Movie/Dir/Prot", and highlight the box
		if (ms.button_left_pressed)
		{
			isTextInvisible = true;
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
		char ascii{};

		//Looping for each available keystate (excluding {BACKSPACE,SPACE})
		//to see if they are being pressed
		for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_Z; i++)
		{
			// If a key is being pressed and we are ready to type again
			if (graphics::getKeyState((graphics::scancode_t)i))
			{
				if (!typed)
				{
					// Convert the key to ASCII and add it to the text field
					ascii = (char)(i + 93);

					timer = 0;	//Reset Timer
					m_characters.push_back(ascii);	//Pushing back to the deque the character the user pressed
					typed = true;
					m_action = true;	//Takes the action (filtering) since we need to find the movies with this parcticular string that the user gave.

					if (isFull)	//If the text field is full, store the first character in a stack and remove it from the text field
					{
						m_inputHistory.push(m_characters[0]);
						m_characters.erase(m_characters.begin());	
					}
				}
			}
			if (graphics::getKeyState((graphics::SCANCODE_SPACE)))	//Check if the SPACE key is being pressed
			{
				if (!typed)	//Add a space to the deque which holds all the m_characters
				{
					timer = 0;
					m_characters.push_back(' ');

					typed = true;
					m_action = true; //Takes the action (filtering) since we need to find the movies with this parcticular string

					//If the text field is full, store the first character in a stack and remove it from the text field, also we keep how many extra words are
					// inserted in tto the stack.
					if (isFull)
					{
						m_inputHistory.push(m_characters[0]);
						m_characters.erase(m_characters.begin());
					}
				}
			}
			if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE))	        //Check if the BACKSPACE key is being pressed
			{
				if (!m_characters.empty() && (!typed))	//If I can type and the m_characters is not empty
				{
					if (isFull)	// If the textfield is full
					{
						if (!m_inputHistory.empty())
						{
							m_characters.push_front(m_inputHistory.top());	//Starting putting back to the beginning of the textfield the words of the stack
							m_inputHistory.pop();	//Removing the world we have already inserted to the front of the word from the stack.
						}
					}

					if (!m_characters.empty())
					{
						m_characters.pop_back();	//Removing from the end of the m_characters deque, since the keyState was BACKSPACE
					}

					typed = true; //set the flag to true since the user has typed
					timer = 0; //Resetting the timer 

				}
				m_action = true;	//Takes the action (filtering) since we need to find the movies with this parcticular string where the character was removed from the end
			}
		}
		timer++;	//Increments the timer

		if (timer > TEXTFIELD_SPEED)	//If the timer surpasses a default value of 8
			typed = false;	//Alerts that the user can now type again

		if (m_characters.size() + m_inputHistory.size() +1 >= MAX_TEXTFIELD_WORDS)	//If m_characters surpasses 25, the textfield is full
		{
			isFull = true;
		}
		else
		{
			isFull = false;
		}
	}

	float TEXT_POSX_OFFSET{ 2.0f };
	const float TEXT_POSY_OFFSET{ 0.1f };

	if (!m_characters.empty())	//If the m_characters is not empty, draw the string
	{
		std::string textfield_string(m_characters.begin(), m_characters.end());
		graphics::drawText(m_positionX - TEXT_POSX_OFFSET, m_positionY + m_height + TEXT_POSY_OFFSET, 0.3f, textfield_string, brush);
	}
	else //else just draw the "Search Movie/Director/Protagonist" text
	{
		TEXT_POSX_OFFSET = 0.8f;
		graphics::drawText(m_positionX - TEXT_POSX_OFFSET, m_positionY + m_height + TEXT_POSY_OFFSET, 0.3f, m_text, brush);
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

	std::string search_string(m_characters.begin(), m_characters.end());   //Making a string out of the deque m_characters

	//For each movie, we check whether this movie is referred given a search_string, based on either each protaginsts, director or title.
	for (const auto& movie : movie_list)
	{
		std::string movie_name = movie->getName();	//Getting the name of the movie we have to create a new string, since we do not want to modify the original when performing lowercase.
		std::string movie_director = movie->getDir();	//Getting the director of the movie we have to create a new string, since we do not want to modify the original when performing lowercase.

		std::transform(movie_name.begin(), movie_name.end(), movie_name.begin(), ::tolower);	// This process,takes the name of the movie and converts it to lowercase
		std::transform(movie_director.begin(), movie_director.end(), movie_director.begin(), ::tolower); // This process,takes the the name of the director and converts it to lowercase

		//Checking if the searching word that was given is referring to a protagonist.
		bool hasProtagonist{ false };

		std::vector<std::string> protagonists = movie->getProtagonists();

		//We are using find() method to see if the inputted string is present in the dir/title of protagonist name, if it isn't it returns the std::string::npos
		for (const auto& protagonist : protagonists)
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
		if ((movie_name.find(search_string) != std::string::npos 
			|| movie_director.find(search_string) != std::string::npos || hasProtagonist)
			&& ((graphics::getKeyState(graphics::SCANCODE_BACKSPACE) || m_characters.empty())))
		{
			if (hasRequirements(movie))
			{
				movie->state_info.setDisabled(false);
				movie->state_info.updateWidgetState(WidgetEnums::WidgetFilters::TitleFilter, WidgetEnums::WidgetFilterState::ENABLED);
				continue;	//If this movie has either title,director,protagonist continue with the next movie
			}
		}

		//If movie title,director or protagonist doesn't have the current textfield title (find() returned npos) anywhere in their name, disable it, and also set the filterstate to be disabled for this movie.
		if (movie_name.find(search_string) == std::string::npos &&
			movie_director.find(search_string) == std::string::npos && !hasProtagonist)
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
	m_characters.clear();
	isTextInvisible = false;
	timer = -1;
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

TextField::TextField(float posX, float posY, const std::string_view text, const TextFieldFiltering::FilterBy& filter, bool invisible)
	: Widget(posX,posY), FilterableWidget(invisible), m_text{ text },m_textfield_filter{filter}
{
	//Inserting all the widgets textfield must check before filtering the movies.
	filterToBeChecked.push_back(WidgetEnums::WidgetFilters::TitleFilter);
	filterToBeChecked.push_back(WidgetEnums::WidgetFilters::GenreFilter);
}