#ifndef MOVIE_H
#define MOVIE_H

#include "sgg/graphics.h"
#include "constants.h"
#include <string>
#include <string_view>
#include <vector>

//=============================================================================================
//=============================================================================================
// 
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

//=============================================================================================
//=============================================================================================

// Struct where we keep all the filtering status for each Movie.
// Filtering Status like genreFilterApplied, textFilterApplied.. helps us sychronize all filters together, when "triggering" a widget

struct MovieFilteringStatus
{
private:

	// filtering status variables
	// They are used in order to inform other widgets that also do filtering, in order to synchronize all filters together.
	bool genreFilterApplied{ true };
	bool textFilterApplied{ true };
	int lastFilterFromYear{ 1950 };
	int lastFilterToYear{ 2020 };

	//Variable that stores all current genres (that where pressed) the movie has.
	int m_genreCount{ 0 };

	//This represents the state where a movie can be and is being updated
	bool m_isUpdatable{ true };

	//Variable used to see if a movie is disabled, a movie is disabled (not updated or drawen) when it doesn't meet filters requirements
	bool m_isDisabled{ false };

	//Used to store if a movie is clicked
	bool m_clickTriggered{ false };

public:

	//Setters and Getters
	int getGenreCount() const { return m_genreCount; }
	void resetGenreCount() { m_genreCount = 0; }
	void AddGenreCount(int g) { m_genreCount += g; }

	void setDisabled(bool d) { m_isDisabled = d; }
	bool isDisabled() const { return m_isDisabled; }

	bool isClickTriggered() const { return m_clickTriggered; }
	void setClickTriggered(bool c) { m_clickTriggered = c; }

	void setUpdatable(bool a) { m_isUpdatable = a; }
	bool isUpdatable() const { return m_isUpdatable; }

	void setGenreFilterApplied(bool g) { genreFilterApplied = g; }
	bool getGenreFilterApplied() const { return genreFilterApplied; }

	void setLastFilterToYear(int y) { lastFilterToYear = y; }
	int getLastFilterToYear() const { return lastFilterToYear; }

	void setLastFilterFromYear(int y) { lastFilterFromYear = y; }
	int getLastFilterFromYear() const { return lastFilterFromYear; }

	bool getTextFilterApplied() const { return textFilterApplied; }
	void setTextFilterApplied(bool t) { textFilterApplied = t; }

};

//=============================================================================================
//=============================================================================================

/*
	Represents a movie and stores information about it, such as the title, description, year of production, and director.
	Also includes control variables that are used to synchronize filters.
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
	std::vector<std::string> m_protagonists;

	// Variables used for "glowing" animation when the mouse hovers the movie frame.
	float m_glow{};
	float m_highlight{};

	bool m_highlighted{ false };
	bool m_PlaySound{ true };

	/*
	 * Determines if the given point (x, y) is inside the border of the "Movies Frame".
	 * @param x The x-coordinate of the point to check.
	 * @param y The y-coordinate of the point to check.
	 * @return True if the point (x, y) is inside the border of the Movies Frame, false otherwise.
	 */
	bool contains(float x, float y) const;

	//Function that displays movies information
	void DisplayInfo();

	class graphics::Brush brush_update1;
	class graphics::Brush brush_update2;
	class graphics::Brush br;

public:

	// Instance where we keep all the filter states for each Movie.
	// Filter States like genreFilterApplied, textFilterApplied.. helps us sychronize all filters together, when clicking on a widget.
	// For Example when clicking "Action" Filter Button ,we want all the movies that have action genre(but not only action) to appear,
	// but if we also want to search for a movie , while action button is still on, we want to only show those movies that have "Action" as genre.
	MovieFilteringStatus MovieFilterState;

	//Vector that stores all genres for a specific movie
	std::vector<std::string> genres;

	// Constructing a new movie
	Movie(const std::string_view n, const std::string_view desc,
		const std::string_view image, const std::string_view year, const std::string_view dir,
		const std::vector<std::string>& prot, const std::vector<std::string>& genre);	

	//Function that draws a movie on the screen
	void draw();

	//Function that updates the movie on the screen
	void update();

	//Function that draws information on the screen box
	void drawInformation();	

	//Getters and Setters
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	void setHighlight(bool h) { m_highlighted = h; }

	const std::string& getName() const;
	const std::string& getDesc() const;
	const std::string& getDate() const;
	const std::string& getDir() const;
};

//=============================================================================================
//=============================================================================================

#endif