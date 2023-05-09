#ifndef MOVIE_H
#define MOVIE_H

#include "sgg/graphics.h"
#include "constants.h"
#include "MovieState.h"

#include <string>
#include <string_view>
#include <vector>


// Represents a drawable box that has movie information when the movie is clicked.
struct InfoBox
{
private:
	// Position X of the box on the screen.
	float m_posX{};

	// Position Y of the box on the screen.
	float m_posY{};

public:
	// Setters and getters for the position of the box.
	void setPosX(float x) { m_posX = x; }
	void setPosY(float y) { m_posY = y; }

	//Return the X position of the movie
	float getPosX() const { return m_posX; }

	//Return the Y position of the movie
	float getPosY() const { return m_posY; }
};

/*
	Represents a movie and stores information about it, such as the title, description, year of production, and director.
*/
class Movie
{
public:

	//Function that draws a movie on the screen
	void draw();

	//Function that updates the movie on the screen
	void update();

	// Function that draws information on the screen box
	void drawMovieInformation();

private:

	// Function that displays movies information
	void displayMovieDetails();
	/*
	 * Determines if the given coordinates of mouse x,y are insde the coordinates of the Movies Frame.
	 * \param mouse_x: the x coordinate of the mouse.
	 * \param mouse_y: the y coordinate of the mouse.
	 * \return True if the given coordinates of mouse x,y is inside the border of the Movies Frame.
	 */
	bool contains(float x, float y) const;

	// Function that returns a new "lines" vector which represents all the lines that should be drawen to the canvas.
	// Based on the whole description of the movie
	const std::vector<std::string> createDescription();

private:

	// Position of the movie on the screen.
	float m_pos[2];

	const std::string m_name{}; // Movie name.

	// Description of the movie.
	const std::string m_description{};

	// Image of the movie.
	const std::string m_image{};

	// Production Year of the movie.
	const std::string m_production_year{};

	// Director of the movie.
	const std::string m_director{};

	//Vector that stores all genres for a specific movie
	const std::vector<std::string> m_genres;

	//Vector that stores all protagonists for a specific movie
	const std::vector<std::string> m_protagonists;

	// Variables used for "glowing" animation when the mouse hovers the movie frame.
	float m_glow{};

	// Variables used for "glowing" animation combined with m_glow, when the mouse hovers the movie frame.
	float m_highlight{};

	bool m_highlighted{ false };
	bool playSound{ true };

	// Represents if the description is created or not.
	bool descriptionCreated{ false };

	// Vector that holds all the lines that should be drawen to the canvas one-by-one
	std::vector<std::string> description_lines;

	//All brushes used.
	graphics::Brush brush;
	graphics::Brush brush2;
	graphics::Brush brush3;
	// Box that displays movie information when clicked.
	InfoBox informationBox;

public:

	// Constructing a new movie
	Movie(const std::string_view n, const std::string_view desc,
		const std::string_view image, const std::string_view year, const std::string_view dir,
		const std::vector<std::string>& prot, const std::vector<std::string>& genre);

	// Instance where we keep all the filtering states,and some other variables (like if it is clicked, or disabeld) for each Movie.
	// For Example when clicking "Action" Filter Button ,we want all the movies that have action genre in their genres, to appear,
	// but if we also want to search for a movie , while action button is still on, we want to only show those movies that have "Action" as genre.
	MovieState state_info;

	//Getters for the information of each movie

	//Returns the name of the movie
	const std::string& getName() const;

	//Returns the description (not tokenized) of the movie
	const std::string& getDesc() const;

	//Returns the released year of the movie
	const std::string& getDate() const;

	//Returns the director of the movie
	const std::string& getDir() const;

	//Returns a vector of all the genres of the movie
	const std::vector<std::string>& getGenres() const;

	//Returns a vector of all the protagonists of the movie
	const std::vector<std::string>& getProtagonists() const;

	//Sets the X position of the movie
	void setPosX(float x) { m_pos[0] = x; }

	//Sets the Y position of the movie
	void setPosY(float y) { m_pos[1] = y; }

	//Sets the highlight of the movie
	void setHighlight(bool h) { m_highlighted = h; }
};

#endif