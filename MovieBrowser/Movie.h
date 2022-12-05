#pragma once

#include <string>
#include <string_view>
#include "sgg/graphics.h"
#include "constants.h"


class Movie
{
private:

	/*
	
	Improvements: Make m_image, name and m_age a char* or char[] for 

	*/

	float m_pos[2];
	std::string m_name{};
	std::string m_description{};

	//Button buttons; an array list of all the categories this movie is so we can make the buttons
	std::string m_age_restriction{};


	std::string m_image{};

	//Add a class Image? and add and istance of this class here so we can save the asset 

	bool m_highlighted{ false };
	bool PlaySound{ true };

	class graphics::Brush br;


public:

	Movie(const std::string_view n, const std::string_view desc, const std::string_view age,const std::string_view);


	void draw();
	void update();

	void setHighlight(bool h) { m_highlighted = h; }

	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	bool contains(float x, float y) const;

	const std::string& getName() const;
	const std::string& getDesc() const;


	void DisplayInfo();

};














