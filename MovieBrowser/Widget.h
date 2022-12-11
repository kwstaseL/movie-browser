#ifndef WIDGET_H
#define WIDGET_H

#include <sgg/graphics.h>
#include "constants.h"
#include "Movie.h"
#include <vector>
#include <string>
#include <iostream>

class Widget
{
protected:

	float m_positionX{};
	float m_positionY{};

	bool m_highlighted{ false };
	bool m_visible{ false };			//Visible only if Dock is down (ex for Buttons)

	bool m_action{ false };

	static inline int s_idGenerator{0};
	int m_uid{};

	graphics::Brush brush;

	static inline int s_focus{0};
	bool requestFocus();
	void releaseFocus();

	bool operating{ false };


public:

	static std::vector<std::string> m_scanned_genres;

	virtual bool isOperating() = 0;
	virtual void setOperating(bool o) = 0;

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual ~Widget();

	virtual bool actionTriggered() = 0;
	virtual void setAction(bool action) = 0;
	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

	Widget(float posX, float posY);

};



#endif






