#include "Movie.h"
#include <cstring>

//COMPLETED FIX THE DRAWING A BIT


// Constructor for Movie class. Initializes member variables with the provided parameters and sets the initial position of the information box.
Movie::Movie(const std::string_view name, const std::string_view desc, const std::string_view image, const std::string_view year, const std::string_view dir, const std::vector<std::string>& prot, const std::vector<std::string>& genre)
	: m_name(name), m_description(desc), m_image(image), m_production_year(year), m_director(dir)
{

	// Inserting genres for the movie into the 'genres' vector
	for (const auto& g : genre)
	{
		genres.push_back(g);
	}

	// Inserting protagonists for the movie into the 'm_protagonists' vector
	for (const auto& pr : prot)
	{
		m_protagonists.push_back(pr);
	}
	
	// Setting the initial position of the information box to the center of the canvas
	informationBox.setPosX(CanvasConst::CANVAS_WIDTH / 2);
	informationBox.setPosY(CanvasConst::CANVAS_HEIGHT / 2);
}

//Function that draws a movie on the screen

void Movie::draw()
{

	// If the movie is disabled, do not draw it.
	if (MovieFilterState.isDisabled())
	{
		return;
	}

	// Calculate glow effect for when the mouse is hovering over the movie.
	m_glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100) * m_highlighted;
	m_highlight = 0.2f * m_highlighted + m_glow * 0.5f;									

	// Draw highlight/glow effect.
	SETCOLOR(brush_update1.fill_color, m_highlight, m_highlight, m_highlight);
	brush_update1.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], MovieConst::Movie_Banner_Width + 0.125f, MovieConst::Movie_Banner_Height + 0.125f, brush_update1);

	//Drawing our Movie image
	brush_update2.outline_opacity = 0.1f;

	brush_update2.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(m_image);
	graphics::drawRect(m_pos[0], m_pos[1], MovieConst::Movie_Banner_Width, MovieConst::Movie_Banner_Height, brush_update2);

}

// Function that updates the movie on the screen.
void Movie::update()
{
	// If the movie is disabled do not update it.
	if (MovieFilterState.isDisabled())
	{
		return;
	}

	// Get mouse state.
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	// Convert mouse coordinates to canvas units.
	float mx{ graphics::windowToCanvasX(ms.cur_pos_x) };
	float my{ graphics::windowToCanvasY(ms.cur_pos_y) };

	// If the mouse is within the bounds of the movie, perform necessary actions.
	if (contains(mx, my)) {

		// If the movie is updatable and not disabled, highlight it and display its information.
		if (MovieFilterState.isUpdatable() && !MovieFilterState.isDisabled())
		{
			if (m_PlaySound)
			{
				graphics::playSound(AssetsConst::ASSET_PATH + static_cast<std::string>("browse.wav"), 0.4f);
			}

			setHighlight(true);
			DisplayInfo();
			m_PlaySound = false;

		}
		//If mouse contains movie, and mouse button left button is pressed,update its state to pressed.
		if (ms.button_left_pressed && MovieFilterState.isUpdatable())	
		{
			MovieFilterState.setClickTriggered(true);	
		}
		//If left button is released , update its state to not pressed.
		if (ms.button_left_released)
		{
			MovieFilterState.setClickTriggered(false);
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
		MovieFilterState.setClickTriggered(false);
	}

}

/*
 * Determines if the given point (x, y) is inside the border of the "Movies Frame".
 * @param x The x-coordinate of the point to check.
 * @param y The y-coordinate of the point to check.
 * @return True if the point (x, y) is inside the border of the Movies Frame, false otherwise.
*/

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


// Function that displays movie information on the "starting screen" 
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

// Function used to draw information about a movie on the screen when the movie is clicked

void Movie::drawInformation()
{
	graphics::Brush brush;

	//Drawing our background image
	// Set the brush properties for the background

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

	// Draw the title of the movie
	graphics::setFont("OpenSans-Semibold.ttf");
	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.6f, CanvasConst::CANVAS_HEIGHT / 6.0f, 1.0f, getName(), br);

	// Draw the image of the movie
	br.outline_opacity = 0.5f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(m_image);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 5.5f, CanvasConst::CANVAS_HEIGHT / 3.8f, MovieConst::Movie_Banner_Width + 0.7f, MovieConst::Movie_Banner_Height + 0.7f, br);

	// Set the font and brush properties for the description
	graphics::setFont("OpenSans-Semibold.ttf");
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 8.0f, CanvasConst::CANVAS_HEIGHT / 2.0f, 0.5f, "Description: ", br);
	graphics::setFont("OpenSans-Light.ttf");


	// Split the description into multiple lines if it is too long to fit on a single line

	std::string description = getDesc();
	char* tokens = &description[0];
	char* context;
	tokens = strtok_s(tokens, " " , &context);

	float count{ 0.0f };
	float height{ 0.0f };

	// Use space as the delimiter and draw each token on its own line

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

	// Draw the director of the movie
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.5f, CanvasConst::CANVAS_HEIGHT / 3.3f, 0.5f, "-Directors:   " + getDir(), br);

	//Draw all protagonists of the movie
	float offset{ 3.5f };
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.5f, CanvasConst::CANVAS_HEIGHT / 2.7f, 0.5f, "-Protagonists: ", br);
	
	for (const auto& protagonist : m_protagonists)
	{
		graphics::setFont("OpenSans-Light.ttf");
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.5f + offset, CanvasConst::CANVAS_HEIGHT / 2.7f, 0.5f, protagonist, br);
		offset += protagonist.size() / 3.5f;
	}

	//Draw all Genres of the movie
	offset = 3.5f;
	graphics::drawText(CanvasConst::CANVAS_WIDTH / 3.6f, CanvasConst::CANVAS_HEIGHT / 4.5f, 0.5f, "Genre: ", br);
	for (const auto& g : genres)
	{
		graphics::setFont("OpenSans-Light.ttf");
		graphics::drawText(CanvasConst::CANVAS_WIDTH / 4.7f + offset, CanvasConst::CANVAS_HEIGHT / 4.5f, 0.5f, g, br);
		offset += g.size() / 3.5f;
	}


}