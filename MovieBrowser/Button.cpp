#include "Button.h"
#include <iostream>


Button::Button(float posX, float posY, const std::string& text)
	:m_button_text(text), Widget(posX, posY)
{}

void Button::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
	float my{ graphics::windowToCanvasX(ms.cur_pos_y) };

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

void Button::draw()
{
	float highlight = 0.2f * m_highlighted;

	SETCOLOR(brush.fill_color, highlight, highlight, highlight);
	brush.outline_opacity = 0.0f;
	graphics::drawRect(m_positionX, m_positionY, m_Genrebutton_width + 0.1, m_Genrebutton_height + 0.1, brush);

	brush.fill_opacity = 1.0f;
	SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(m_positionX - 0.45f, m_positionY + 0.125f, 0.4f, m_button_text, brush);


	SETCOLOR(brush.fill_color, 0.0f, 0.0f, 0.0f);

	//Draw our button
	brush.texture = "";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.2f;
	graphics::drawRect(m_positionX, m_positionY, m_Genrebutton_width, m_Genrebutton_height, brush);

}

void Button::takeAction(const std::vector<Movie*>& movie_list)
{
	if (m_uid >= 0 && m_uid <=2)
	{
		filterByGenre(movie_list);
	}
	else if (m_uid == 3)
	{
		//resetFilter();
	}
	
}

bool Button::contains(float x, float y) const
{
	return FunctionsConst::distance(x, y, m_positionX, m_positionY) < m_Genrebutton_height * m_Genrebutton_width * 0.14f;

}

void Button::filterByGenre(const std::vector<Movie*>& movie_list) const
{
	std::cout << "Button with id: " << m_uid << std::endl;

	bool hasGenre{};
	s_scanned_genres.push_back(m_button_text);

	for (const auto& movie : movie_list)
	{
		hasGenre = false;
		for (const auto& pressed_genres : s_scanned_genres)
		{
			for (const auto& genre : movie->genres)
			{
				if (genre == pressed_genres)
				{
					movie->setDisabled(false);
					hasGenre = true;
				}
				else
				{
					movie->setDisabled(true);
				}
			}
		}
		if (hasGenre)
		{
			movie->setDisabled(false);
		}
		else
		{
			movie->setDisabled(true);
		}
	}

	/*
	bool hasGenre;

	for (const auto& movie : movie_list)
	{
		hasGenre = false;
		if (movie)
		{
			for (const auto& movie_genre : movie->genres)
			{
				std::cout << "Now scanning for movie_genre" << movie_genre << std::endl;
				if (movie_genre == m_button_text || hasGenre)
				{
					hasGenre = true;
					if (!s_scanned_genres.empty())	//Edw thelei ftiajimo
					{

						//Find if it is equal with already scanned movies
						for (const auto& already_scanned_genre : s_scanned_genres)
						{
							std::cout << "Movie Genre here is : " << movie_genre << std::endl;
							std::cout << "Already Scanned Genre here is : " << already_scanned_genre << std::endl;

							if (movie_genre == already_scanned_genre && already_scanned_genre != m_button_text)
							{
								movie->setDisabled(false);
								break;
							}
							else
							{
								movie->setDisabled(true);
							}
						}
						if (!movie->isDisabled())
						{
;							break;
						}
					}
					else
					{
						movie->setDisabled(false);
						break;
					}
				}
				else
				{
					movie->setDisabled(true);
				}
			}

		}
		else
		{
			continue;
		}
	}
	s_scanned_genres.push_back(m_button_text);
	*/
}


