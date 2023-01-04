#ifndef MOVIE_H
#define MOVIE_H

#include "sgg/graphics.h"
#include "constants.h"
#include <string>
#include <string_view>
#include <vector>

//Represents a Box, when a movie is clicked, information is being drawned inside that box
struct Box
{
private:

	float m_posX{};
	float m_posY{};

public:

	void setPosX(float x) { m_posX = x; }
	void setPosY(float y) { m_posY = y; }

	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }

};

/*
	Represents the Movie class where we keep information about each movie (description,title,year..) and some control variables that 
	help us maintain all filters together
*/

class Movie
{
private:

	float m_pos[2];	//Position X and Y of a movie to the canvas

	std::string m_name{}; //Movie name

	Box informationBox;	//Information box displayed when pressing a movie


	//Information about movies

	const std::string m_description{};
	const std::string m_image{};
	const std::string m_production_year{};
	const std::string m_director{};

	std::vector<std::string> m_protagonists;

	float m_glow{};	//	Glow is a float that we use to highlight
	float m_highlight{};

	bool m_highlighted{ false };
	bool m_PlaySound{ true };


	//Control variables that we use in order to synchronize all filter patterns

	bool hasFilteredGenre{ true };
	bool hasFilteredText{ true };

	int lastYearComparedfromTo{ 2020 };
	int lastYearComparedFrom{ 1950 };

	//Variable that stores all genres that the movie has.
	int m_genreCount{ 0 };

	
	bool m_active{ true };	//This represents the state where a movie can be and is being updated
	bool m_disabled{ false };	//Variable used to see if a movie is disabled, a movie is disabled (not updated or drawen) when it doesn't meet filters requirements
	bool m_clickTriggered{ false };	//Used to store if a movie is clicked

	bool contains(float x, float y) const;	//Takes in mouse_x , and mouse_y from getMouseState and returns if the mouse is in Movies Frame Borders

	void DisplayInfo();	//Function that displays movies information

	class graphics::Brush brush_update1;
	class graphics::Brush brush_update2;
	class graphics::Brush br;

public:

	std::vector<std::string> genres;	//Vector that stores all genres for a specific movie

	Movie(const std::string_view n, const std::string_view desc,
		const std::string_view image, const std::string_view year, const std::string_view dir,
		const std::vector<std::string>& prot, const std::vector<std::string>& genre);	//Constructor

	void draw();	//Function that draws a movie on the screen
	void update();	//Function that updates the movie on the screen

	void drawInformation();	//Function that draws information on the screen

	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	int getGenreCount() const { return m_genreCount; }
	void resetGenreCount() { m_genreCount = 0; }
	void AddGenreCount(int g) { m_genreCount += g; }

	void setDisabled(bool d) { m_disabled = d; }
	bool isDisabled() const { return m_disabled; }

	bool isClickTriggered() const { return m_clickTriggered; }

	void setHighlight(bool h) { m_highlighted = h; }

	void setActive(bool a) { m_active = a; }
	bool isActive() const { return m_active; }

	void sethasFilteredGenre(bool g) { hasFilteredGenre = g; }
	bool gethasFilteredGenre() const { return hasFilteredGenre; }

	void setLastYearComparedfromTo(int y) { lastYearComparedfromTo = y; }
	int getLastYearComparedfromTo() const { return lastYearComparedfromTo; }

	void setLastYearComparedFrom(int y) { lastYearComparedFrom = y; }
	int getLastYearComparedFrom() const { return lastYearComparedFrom; }

	bool getHasFilteredText() const { return hasFilteredText; }
	void sethasFilteredText(bool t) { hasFilteredText = t; }

	const std::string& getName() const;
	const std::string& getDesc() const;
	const std::string& getDate() const;
	const std::string& getDir() const;
};

#endif