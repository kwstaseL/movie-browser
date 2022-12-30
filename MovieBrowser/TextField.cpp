#include "TextField.h"
#include <algorithm>


bool TextField::hasRequirements(const Movie* movie) const
{
	if (movie)
	{
		return movie->gethasFilteredGenre() && std::stoi(movie->getDate()) <= movie->getLastYearComparedfromTo() && std::stoi(movie->getDate()) >= movie->getLastYearComparedFrom();
	}
	return false;
}

void TextField::draw()
{
	if (!m_visible)
	{
		return;
	}

	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.5f * m_highlighted, 0.5f * m_highlighted, 0.5f * m_highlighted);
	brush.outline_opacity = 1.0f;
	graphics::drawRect(m_positionX, m_positionY + m_height, m_Textfield_width, m_Textfield_height, br);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (!textInvisible && characters.empty())
	{
		graphics::drawText(m_positionX - 0.8f, m_positionY + m_height + 0.1f, 0.3f, m_text, br);
	}

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

	if (contains(mouse_X, mouse_Y))
	{
		if (ms.button_left_pressed)
		{
			textInvisible = true;
			m_highlighted = true;
		}
	}
	else
	{
		if (ms.button_left_pressed)
		{
			m_highlighted = false;
		}
	}


	if (m_highlighted)
	{
		if (graphics::getKeyState(graphics::SCANCODE_A))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('a');

				m_typed = true;
				setActionTriggered(true);

			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_B))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('b');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_C))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('c');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_D))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('d');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_E))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('e');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_F))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('f');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_G))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('g');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_H))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('h');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_I))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('i');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_J))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('j');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_K))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('k');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_L))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('l');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_M))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('m');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_N))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('n');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_O))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('o');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_P))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('p');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_Q))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('q');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_R))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('r');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_S))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('s');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_T))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('t');
				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_U))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('u');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_V))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('v');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_W))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('w');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_X))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('x');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_Y))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('y');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_Z))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back('z');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		{
			if (!m_typed)
			{
				m_counter = 0;
				characters.push_back(' ');

				m_typed = true;
				setActionTriggered(true);

			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE))
		{
			if (!characters.empty() && !m_typed)
			{
				m_counter = 0;
				characters.pop_back();
				m_typed = true;
			}
			setActionTriggered(true);
		}
		
		m_counter++;
		if (m_counter > 20)
			m_typed = false;
	}

	if (!characters.empty())
	{
		std::string string(characters.begin(), characters.end());
		graphics::drawText(m_positionX - 1.9f, m_positionY + m_height + 0.1f, 0.3f, string, brush);
	}
	else
	{
		graphics::drawText(m_positionX - 0.8f, m_positionY + m_height + 0.1f, 0.3f, m_text, brush);
	}
}

void TextField::takeAction(const std::vector<Movie*>& movie_list)
{
	searchByTitle(movie_list);
}


void TextField::searchByTitle(const std::vector<Movie*>& movie_list)
{
	if (!requestFocus())
	{
		return;
	}

	std::string string(characters.begin(), characters.end());

	for (const auto& movie : movie_list)
	{
		std::string movie_name = movie->getName();
		std::transform(movie_name.begin(), movie_name.end(), movie_name.begin(), ::tolower);

		if (movie_name.find(string) != std::string::npos && graphics::getKeyState(graphics::SCANCODE_BACKSPACE) || characters.empty())
		{
			if (hasRequirements(movie))
			{
				movie->setDisabled(false);
				movie->sethasFilteredText(true);
			}
		}

		if (movie_name.find(string) == std::string::npos)
		{
			movie->setDisabled(true);
			movie->sethasFilteredText(false);
		}
		else
		{
			movie->sethasFilteredText(true);
		}


	}
	setActionTriggered(false);
	operating = false;
	releaseFocus();
}

bool TextField::contains(float x, float y) const
{
	return FunctionsConst::distance(x, y, m_positionX, m_positionY + m_height) < m_Textfield_height / 10.0f * m_Textfield_width + 0.25f;
}

void TextField::deleteText()
{
	characters.clear();
	textInvisible = false;
}

TextField::TextField(float posX, float posY, const std::string_view text)
	:Widget(posX, posY), m_text{ text } {}
