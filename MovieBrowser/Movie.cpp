#include "Movie.h"

Movie::Movie(const std::string_view name, const std::string_view desc, const std::string_view image, const std::string_view year, const std::string_view dir, const std::vector<std::string>& prot, const std::vector<std::string>& genre)
	: m_name(name), m_description(desc), m_image(image), m_production_year(year), m_director(dir)
{
	for (const auto& g : genre)
	{
		genres.push_back(g);
	}

	for (const auto& pr : prot)
	{
		m_protagonists.push_back(pr);
	}

	informationBox.setPosX(CanvasConst::CANVAS_WIDTH / 2);
	informationBox.setPosY(CanvasConst::CANVAS_HEIGHT / 2);

}

void Movie::draw()
{
	if (isDisabled())
	{
		return;
	}

	m_glow =  0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100) * m_highlighted;		//This is for our glow when doing mouse over movie
	m_highlight = 0.2f * m_highlighted + m_glow * 0.5f ;									//If we mouse over a movie, then it gets highlighted

	//Drawing our highlight/glow

	SETCOLOR(brush_update1.fill_color, m_highlight, m_highlight, m_highlight);
	brush_update1.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], MovieConst::Movie_Banner_Width + 0.125f, MovieConst::Movie_Banner_Height + 0.125f, brush_update1);

	//Drawing our Movie

	brush_update2.outline_opacity = 0.1f;

	brush_update2.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(m_image);
	graphics::drawRect(m_pos[0], m_pos[1], MovieConst::Movie_Banner_Width, MovieConst::Movie_Banner_Height, brush_update2);
	graphics::resetPose();

}

void Movie::update()
{

	if (isDisabled())
	{
		return;
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);	//Fills our ms state, ms inside has states of our mouse , button left pressed, button left down..

	float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
	float my{ graphics::windowToCanvasY(ms.cur_pos_y) };

	if (contains(mx, my)) {

		if (m_active && !isDisabled())
		{
			if (m_PlaySound)
			{
				graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("browse.wav"), 0.4f);
			}
			setHighlight(true);
			DisplayInfo();
			m_PlaySound = false;
		}
		if (ms.button_left_pressed && isActive())
		{
			m_clickTriggered = true;
		}
		else if (ms.button_left_released)
		{
			m_clickTriggered = false;
		}

	}
	else
	{
		m_PlaySound = true;
		setHighlight(false);
	}

	if (!(informationBox.containsMovie(mx,my)))
	{
		
		m_clickTriggered = false;
		
	}

}

bool Movie::contains(float x, float y) const
{
	return FunctionsConst::distance(x, y, m_pos[0], m_pos[1]) < MovieConst::Movie_Banner_Height*1.05f * MovieConst::Movie_Banner_Width* 0.14f;
}

const std::string& Movie::getName() const
{
	return m_name;
}

const std::string& Movie::getDesc() const
{
	return m_description;
}

const std::string& Movie::getDate() const
{
	return m_production_year;
}

const std::string& Movie::getDir() const
{
	return m_director;
}


void Movie::DisplayInfo()
{
	
	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	graphics::setFont("OpenSans-Semibold.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f - 1.0f, CanvasConst::CANVAS_HEIGHT / 1.35f, 1.0f, getName(), br);

	graphics::setFont("OpenSans-Regular.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f, CanvasConst::CANVAS_HEIGHT / 1.20f, 0.5f, getDate(), br);
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f, CanvasConst::CANVAS_HEIGHT / 1.15f, 0.5f, getDir(), br);


	graphics::setFont("OpenSans-Regular.ttf");
	float offset{ 0.0f };
	for (const auto& protagonist : m_protagonists)
	{
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f + offset, CanvasConst::CANVAS_HEIGHT / 1.10f, 0.5f, protagonist, br);
		offset += protagonist.size()/3;
	}

	offset = 0.0f;
	for (const auto& g : genres)
	{
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f+offset, CanvasConst::CANVAS_HEIGHT / 1.28, 0.5f, g, br);
		offset += g.size()/2.9f;
	}

}

void Movie::drawInformation()
{
	graphics::Brush brush;

	br.fill_opacity = 0.5f;
	br.outline_opacity = 0.0f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::BACKGROUND);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT, br);

	//Drawing box
	SETCOLOR(brush.fill_color, 0.0f, 0.0f, 0.0f);
	brush.texture = "";
	brush.fill_opacity = 0.7f;
	brush.outline_opacity = 0.3f;
	graphics::drawRect(informationBox.getPosX(), informationBox.getPosY(), CanvasConst::CANVAS_WIDTH / 1.2, CanvasConst::CANVAS_HEIGHT / 1.2, brush);

	//Drawing title
	graphics::setFont("OpenSans-Semibold.ttf");
	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.6f, CanvasConst::CANVAS_HEIGHT / 6.0f, 1.0f, getName(), br);


	//Drawing picture
	br.outline_opacity = 0.5f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(m_image);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 5.5f, CanvasConst::CANVAS_HEIGHT / 3.8f, MovieConst::Movie_Banner_Width + 0.7f, MovieConst::Movie_Banner_Height + 0.7f, br);

	//Description
	graphics::setFont("OpenSans-Regular.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 8.0f, CanvasConst::CANVAS_HEIGHT / 2.0f,0.5f,"Description: ", br);
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 8.0f, CanvasConst::CANVAS_HEIGHT / 1.65f, 0.5f, getDesc(), br);



	//Drawing info
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.4f + getName().size()/2.5f + 1.10f, CanvasConst::CANVAS_HEIGHT / 6.25f, 0.7f, + "(" + getDate() + ")", br);
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.4f, CanvasConst::CANVAS_HEIGHT / 3.3f, 0.5f, "-Directors: " + getDir(), br);



	float offset{ 3.5f };
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.4f, CanvasConst::CANVAS_HEIGHT / 2.7f, 0.5f, "-Protagonists: ", br);
	for (const auto& protagonist : m_protagonists)
	{
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.4f + offset, CanvasConst::CANVAS_HEIGHT / 2.7f, 0.5f, protagonist, br);
		offset += protagonist.size()/3.7f;
	}

	offset = 3.5f;
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.6f, CanvasConst::CANVAS_HEIGHT / 4.5f, 0.5f, "Genre: ", br);
	for (const auto& g : genres)
	{
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 4.1f + offset, CanvasConst::CANVAS_HEIGHT / 4.5f, 0.5f, g, br);
		offset += g.size() / 2.9f;
	}
}


bool Box::containsMovie(float x,float y) const
{
	return FunctionsConst::distance(x, y, m_posX, m_posY) < (CanvasConst::CANVAS_WIDTH / 1.2 * CanvasConst::CANVAS_HEIGHT / 1.2) * 0.040f;
}
