#include "TextField.h"
#include <algorithm>
#include <iostream>


void TextField::draw()
{
	if (!m_visible)
	{
		return;
	}

	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.5f, 0.5f, 0.5f);
	graphics::drawRect(m_positionX, m_positionY + m_height, 4.0f, 0.5f, br);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(m_positionX - 3.0f, m_positionY + 4.1f, 0.3f, m_text, br);
}

void TextField::update()
{
	if (!m_visible)
	{
		return;
	}

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

	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		if (!m_typed)
		{
			m_counter = 0;
			characters.push_back('a');
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator++;
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
			iterator--;
			m_typed = true;
		}
		setActionTriggered(true);
	}

	if (!characters.empty())
	{
		std::string string(characters.begin(), characters.end());
		graphics::drawText(m_positionX - 1.9f, m_positionY + 4.1f, 0.3f, string, brush);
	}

	m_counter++;
	if (m_counter > 20)
		m_typed = false;
}

void TextField::takeAction(const std::vector<Movie*>& movie_list)
{
	if (!requestFocus())
	{
		return;
	}

	std::string string(characters.begin(), characters.end());
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);


	for (const auto& movie : movie_list)
	{
		std::string movie_name = movie->getName();
		std::transform(movie_name.begin(), movie_name.end(), movie_name.begin(), ::tolower);

		if (movie_name.find(string) != std::string::npos && graphics::getKeyState(graphics::SCANCODE_BACKSPACE) || characters.empty())
		{
			if (movie->gethasFilteredGenre() && std::stoi(movie->getDate()) <= movie->getLastYearComparedfromTo())
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
	return FunctionsConst::distance(x, y, m_positionX, m_positionY);
}

void TextField::deleteText()
{
	characters.clear();
}

TextField::TextField(float posX, float posY, const std::string_view text)
	:Widget(posX, posY), m_text{ text } {}