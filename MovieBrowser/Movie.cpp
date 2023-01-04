#include "Movie.h"
#include <cstring>


Movie::Movie(const std::string_view name, const std::string_view desc, const std::string_view image, const std::string_view year, const std::string_view dir, const std::vector<std::string>& prot, const std::vector<std::string>& genre)
	: m_name(name), m_description(desc), m_image(image), m_production_year(year), m_director(dir)
{
	for (const auto& g : genre)	//Inserting on a vector all genres for a movie
	{
		genres.push_back(g);
	}

	for (const auto& pr : prot)	//Inserting on a vector all protagonists for a movie
	{
		m_protagonists.push_back(pr);
	}
	
	//Setting informationBox on the center of our canvas
	informationBox.setPosX(CanvasConst::CANVAS_WIDTH / 2);
	informationBox.setPosY(CanvasConst::CANVAS_HEIGHT / 2);
}


//Drawing our movie
void Movie::draw()
{
	if (isDisabled())	//If movie is Disabled then return
	{
		return;
	}

	m_glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100) * m_highlighted;		//This is for our glow when doing mouse over movie and it starts glowing
	m_highlight = 0.2f * m_highlighted + m_glow * 0.5f;									

	//Drawing our highlight/glow

	SETCOLOR(brush_update1.fill_color, m_highlight, m_highlight, m_highlight);
	brush_update1.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], MovieConst::Movie_Banner_Width + 0.125f, MovieConst::Movie_Banner_Height + 0.125f, brush_update1);

	//Drawing our Movie image
	brush_update2.outline_opacity = 0.1f;

	brush_update2.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(m_image);
	graphics::drawRect(m_pos[0], m_pos[1], MovieConst::Movie_Banner_Width, MovieConst::Movie_Banner_Height, brush_update2);

}

//Updating movie
void Movie::update()
{

	if (isDisabled())	//If movie is Disabled then return
	{
		return;
	}

	//Getting Mouse State
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
	float my{ graphics::windowToCanvasY(ms.cur_pos_y) };

	//If mouse contains -> means is in Movie's borders
	if (contains(mx, my)) {

		if (m_active && !isDisabled())	//If movie is not disabled
		{
			if (m_PlaySound)
			{
				graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("browse.wav"), 0.4f);
			}

			setHighlight(true);
			DisplayInfo();
			m_PlaySound = false;

		}
		if (ms.button_left_pressed && isActive())	//If mouse contains movie, and mouse button left button is pressed,update its state to pressed
		{
			m_clickTriggered = true;	
		}
		if (ms.button_left_released)	//If left button is released , update its state to not pressed
		{
			m_clickTriggered = false;
		}

	}
	else
	{
		m_PlaySound = true;
		setHighlight(false);
	}

	//If mouse doesnt contain anymore and mouse is released then again we update its state to not pressed
	if (ms.button_left_released)
	{

		m_clickTriggered = false;

	}

}

// Function that determines if mouse_x and mouse_y is in borders of our movie frame 

bool Movie::contains(float mouse_x, float mouse_y) const
{
	return (mouse_x > m_pos[0] - MovieConst::Movie_Banner_Width / 2 && mouse_x < m_pos[0] + MovieConst::Movie_Banner_Width / 2 && mouse_y > m_pos[1] - MovieConst::Movie_Banner_Height / 2 && mouse_y < m_pos[1] + MovieConst::Movie_Banner_Height / 2);
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


// Function that displays movie information 

void Movie::DisplayInfo()
{

	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	//Drawing the Movies Name
	graphics::setFont("OpenSans-Semibold.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f - 1.0f, CanvasConst::CANVAS_HEIGHT / 1.35f, 1.0f, getName(), br);

	//Drawing the Movies Date
	graphics::setFont("OpenSans-Regular.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f, CanvasConst::CANVAS_HEIGHT / 1.20f, 0.5f, getDate(), br);

	//Drawing the Movies Directors
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f, CanvasConst::CANVAS_HEIGHT / 1.15f, 0.5f, getDir(), br);

	graphics::setFont("OpenSans-Regular.ttf");


	//For all protagonists, draw the protagonist
	float offset{ 0.0f };
	for (const auto& protagonist : m_protagonists)
	{
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f + offset, CanvasConst::CANVAS_HEIGHT / 1.10f, 0.5f, protagonist, br);
		offset += protagonist.size() / 3;
	}


	//For all genres, draw the genre
	offset = 0.0f;
	for (const auto& g : genres)
	{
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 15.0f + offset, CanvasConst::CANVAS_HEIGHT / 1.28, 0.5f, g, br);
		offset += g.size() / 2.9f;
	}

}

//Function used to draw information when we change state to when movie is clicked

void Movie::drawInformation()
{
	graphics::Brush brush;

	//Drawing our background

	br.fill_opacity = 0.5f;
	br.outline_opacity = 0.0f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::BACKGROUND);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT, br);

	//Drawing outside box of movie information
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

	//Drawing description
	graphics::setFont("OpenSans-Semibold.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 8.0f, CanvasConst::CANVAS_HEIGHT / 2.0f, 0.5f, "Description: ", br);
	graphics::setFont("OpenSans-Light.ttf");

	std::string description = getDesc();
	char* tokens = &description[0];
	char* context;
	tokens = strtok_s(tokens, " " , &context);

	// Use space as the delimiter
	// Print each token
	float count{ 0.0f };
	float height{ 0.0f };
	while (tokens != nullptr) {

		if (count >= 15.0f)
		{
			count = 0;
			height += .7f;
		}

		graphics::drawText(CanvasConst::CANVAS_WIDTH / 8.0f + count, CanvasConst::CANVAS_HEIGHT / 1.65f + height, 0.5f, tokens, br);
		count += strlen(tokens)/4.5f +0.35f;
		tokens = strtok_s(nullptr, " ",&context);

	}

	//Drawing year of movie
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.4f + getName().size() / 2.5f + 1.2f, CanvasConst::CANVAS_HEIGHT / 6.25f, 0.7f, +"(" + getDate() + ")", br);
	graphics::setFont("OpenSans-Light.ttf");

	//Drawing director
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.5f, CanvasConst::CANVAS_HEIGHT / 3.3f, 0.5f, "-Directors:   " + getDir(), br);

	//Drawing all protagonists
	float offset{ 3.5f };
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.5f, CanvasConst::CANVAS_HEIGHT / 2.7f, 0.5f, "-Protagonists: ", br);
	
	for (const auto& protagonist : m_protagonists)
	{
		graphics::setFont("OpenSans-Light.ttf");
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.5f + offset, CanvasConst::CANVAS_HEIGHT / 2.7f, 0.5f, protagonist, br);
		offset += protagonist.size() / 3.5f;
	}


	//Drawing all Genres
	offset = 3.5f;
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.6f, CanvasConst::CANVAS_HEIGHT / 4.5f, 0.5f, "Genre: ", br);
	for (const auto& g : genres)
	{
		graphics::setFont("OpenSans-Light.ttf");
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 4.7f + offset, CanvasConst::CANVAS_HEIGHT / 4.5f, 0.5f, g, br);
		offset += g.size() / 3.5f;
	}


}