#ifndef MOVIE_H
#define MOVIE_H

#include "sgg/graphics.h"
#include "constants.h"

#include <string>
#include <string_view>
#include <vector>
#include "MovieState.h"


// Represents a drawable box that has movie information when the movie is clicked.
struct InfoBox
{
private:

	// Position of the box on the screen.
	float m_posX{};
	float m_posY{};

public:
	// Setters and getters for the position of the box.
	void setPosX(float x) { m_posX = x; }
	void setPosY(float y) { m_posY = y; }
	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }
};

/*
	Represents a movie and stores information about it, such as the title, description, year of production, and director.
*/
class Movie
{
private:

	// Position of the movie on the screen.
	float m_pos[2];

	std::string m_name{}; // Movie name.

	// Box that displays movie information when clicked.
	InfoBox informationBox;

	// Movie information.
	const std::string m_description{};
	const std::string m_image{};
	const std::string m_production_year{};
	const std::string m_director{};

	// Function that displays movies information
	void DisplayInfo();

	class graphics::Brush brush_update1;
	class graphics::Brush brush_update2;
	class graphics::Brush br;

	// Variables used for "glowing" animation when the mouse hovers the movie frame.
	float m_glow{};
	float m_highlight{};

	bool m_highlighted{ false };
	bool m_PlaySound{ true };

	/*
	 * Determines if the given coordinates of mouse x,y are insde the coordinates of the Movies Frame.
	 * \param mouse_x: the x coordinate of the mouse.
	 * \param mouse_y: the y coordinate of the mouse.
	 * \return True if the given coordinates of mouse x,y is inside the border of the Movies Frame.
	 */
	bool contains(float x, float y) const;

public:

	// Instance where we keep all the filtering states for each Movie.
	// For Example when clicking "Action" Filter Button ,we want all the movies that have action genre in their genres, to appear,
	// but if we also want to search for a movie , while action button is still on, we want to only show those movies that have "Action" as genre.
	MovieState state_info;

	//Vector that stores all genres for a specific movie
	std::vector<std::string> genres;
	std::vector<std::string> m_protagonists;


	// Constructing a new movie
	Movie(const std::string_view n, const std::string_view desc,
		const std::string_view image, const std::string_view year, const std::string_view dir,
		const std::vector<std::string>& prot, const std::vector<std::string>& genre);	

	//Function that draws a movie on the screen
	void draw();

	//Function that updates the movie on the screen
	void update();

	// Function that draws information on the screen box
	void drawInformation();	

	//Getters and Setters
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	void setHighlight(bool h) { m_highlighted = h; }

	// Function that returns a new "lines" vector which represents all the lines that should be drawen to the canvas.
	// Based on the whole description of the movie
	const std::vector<std::string> createDescription();

	// Represents if the description is created or not.
	bool descriptionCreated{ false };

	// Vector that holds all the lines that should be drawen to the canvas one-by-one
	std::vector<std::string> lines;

	//Getters for the information of each movie

	const std::string& getName() const;
	const std::string& getDesc() const;
	const std::string& getDate() const;
	const std::string& getDir() const;
};

#endif