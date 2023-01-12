#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

class Button : public Widget
{
protected:

	//Enum class representing the different states of a button: idle, pressed, or highlighted.
	enum class button_state_t {

		BUTTON_IDLE,       //Button is not being pressed or highlighted
		BUTTON_PRESSED,    //Button is being pressed
		BUTTON_HIGHLIGHTED //Button is being highlighted (mouse is hovering over it)

	};

	//The text displayed on the button ("Action","Drama",...,"Clear Filter")
	std::string m_button_text{};

	const float m_Genrebutton_height{ .5f };
	const float m_Genrebutton_width{ 3.0f };

	button_state_t m_button_state{ button_state_t::BUTTON_IDLE };

	//This represents how much height will the button need in order to appear when the dock comes down
	float m_height_offset{ 2.0f };
	float getHeightOffset() const override { return m_height_offset; }

	//Checks if the mouse is within the coordinates of the button
	// \param mouse_x: the x coordinate of the mouse
	// \param mouse_y: the y coordinate of the mouse
	// \return true if the mouse is within the button's coordinates, false otherwise
	bool contains(float mouse_x, float mouse_y) const;

private:

	//Continuously updates the button
	virtual void update() = 0;

	//Continuously draws the button on the screen.
	virtual void draw() = 0;

	//Resets the button's state
	virtual void clear() = 0;

	//Performs an action(e.g.filter movies) when the button is pressed.
	//This function is being called when the button is pressed to perform the action depending on the button.
	//(When filtering, the Buttons which filters the genres take into consideration all the other widgets that may have filtered the movies.)
	// \param movie_list: a vector of all the movies
	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

public:

	//Constructs a new button
	// \param posX: the x coordinate of the button's position
	// \param posY: the y coordinate of the button's position
	// \param text: the text displayed on the button
	Button(float posX, float posY, const std::string_view text);
	virtual ~Button() = default;

};



#endif
