#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include <unordered_set>

//COMPLETED

/*
	 A class representing a button widget in a user interface.
	The button has a text label and can be pressed to perform an action (e.g. filter movies, reset filter).
	The Button class is derived from the Widget class, which provides a common interface for interacting with different types of widgets.
	When filtering, the Buttons which filters the genres take into consideration all the other widgets that may have filtered the movies.

*/
class Button : public Widget
{
protected:

	// An enum class representing the different states of a button: idle, pressed, or highlighted
	enum class button_state_t {

		BUTTON_IDLE,       // Button is not being pressed or highlighted
		BUTTON_PRESSED,    // Button is being pressed
		BUTTON_HIGHLIGHTED // Button is being highlighted (mouse is hovering over it)
	};

	// The text displayed on the button ("Action","Drama",...,"Clear Filter")
	std::string m_button_text{};

	// The height and width of every button
	const float m_Genrebutton_height{ .5f };
	const float m_Genrebutton_width{ 3.0f };

	// Initialize the button state to IDLE
	button_state_t m_button_state{ button_state_t::BUTTON_IDLE };

	// Checks if the mouse is within the boundaries of the button
	// @param mouse_x: the x coordinate of the mouse
	// @param mouse_y: the y coordinate of the mouse
	// @return true if the mouse is within the button's coordinates, false otherwise
	bool contains(float mouse_x, float mouse_y) const;

private:

	// Continuously updates the button's state by checking for changes 
	// in the button's state (e.g. when the mouse is hovering over the button or when the button is being pressed)
	virtual void update() = 0;

	//Repeatedly draws the button on the screen.
	virtual void draw() = 0;

	// Resets the button's states
	virtual void clear() = 0;

	// Performs an action(e.g.filter movies) when the button is pressed
	// This function is be called when the button is pressed to perform the action depending on the button.
	// @param movie_list: a vector of all the movies to be filtered
	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

public:

	// Constructs a new button
	// @param posX: the x coordinate of the button's position
	// @param posY: the y coordinate of the button's position
	// @param text: the text displayed on the button
	Button(float posX, float posY, const std::string_view text);
	virtual ~Button() = default;

};



#endif
