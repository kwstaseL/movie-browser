#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include <unordered_set>


class Button : public Widget
{
protected:

	//Enum class which represents if a button is idle,pressed,or highlighted
	enum class button_state_t {

		BUTTON_IDLE,
		BUTTON_PRESSED,
		BUTTON_HIGHLIGHTED

	};

	std::string m_button_text{};	//Text that each button has ("Action","Drama"..,"Clear Filter")

	//Height and width of every button
	const float m_Genrebutton_height{ .5f };
	const float m_Genrebutton_width{ 3.0f };

	button_state_t m_button_state{ button_state_t::BUTTON_IDLE };
	
	bool contains(float x, float y) const;	//Takes in mouse_x , and mouse_y from getMouseState and returns if the mouse is in Buttons Borders

private:

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clear() = 0;


	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

public:

	Button(float posX, float posY, const std::string_view text);
	virtual ~Button() = default;

};



#endif



