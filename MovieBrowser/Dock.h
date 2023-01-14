#ifndef DOCK_H
#define DOCK_H

#include "Widget.h"

//This class represents the Dock, which when hovered with the mouse, comes down to reveal all the widgets we use.

class Dock final : public Widget
{
private:

	//Representing the different states of our dock: idle, going down, or going up
	enum class m_dock_status
	{
		STATE_IDLE,				// Dock is not being hovered or its moving.
		STATE_GOING_DOWN,		// Dock is hovered and is coming down.
		STATE_GOING_UP			// Dock was previously hovered and now is going up.
	};

	const float m_dock_height{ CanvasConst::CANVAS_HEIGHT / 2 };
	const float m_dock_width{ CanvasConst::CANVAS_WIDTH / 2 };

	m_dock_status m_dock_state{ m_dock_status::STATE_IDLE };

	//This offset is used when the dock is sliding down in order to extend the area where the mouse can be.
	float m_offset{ -15.0f };

	//A boolean variable to play the sound of the dock sliding only once.
	bool PlaySound{ true };

	//Indicates if all the widgets are up and invisible
	bool allWidgetsUp{ true };

	//A vector containing all the widgets that will appear inside the dock.
	std::vector<Widget*> widgets;

private:

	//Checks if the mouse is within the coordinates of the dock.
	// \param mouse_x: the x coordinate of the mouse
	// \param mouse_y: the y coordinate of the mouse
	// \return true if the mouse is within the dock's coordinates
	bool contains(float mouse_x, float mouse_y) const;

	//Sets all movies as not updatable or updatable using the `movie_list` depending if the dock is going down or it's going up, 
	//\param movie_list: a vector of all our movies
	void takeAction(const std::vector<Movie*>& movie_list) override;

	//Resets the docks state
	void clear() override;

	//Function that continuously updates our dock
	void update() override;

	//Function that continuously draws our dock
	void draw() override;

public:

	//Constructs a new Dock
	//  \param float x: The x coordinate of the dock's position.
	//  \param float y: The y coordinate of the docks position.
	//  \param const std::vector<Widget*>& widgets_list: a vector of our Widgets.
	Dock(float x, float y, const std::vector<Widget*>& widgets_list);
	virtual ~Dock() = default;

};

#endif