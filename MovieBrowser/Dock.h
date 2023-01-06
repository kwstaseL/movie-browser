#ifndef DOCK_H
#define DOCK_H

#include "Widget.h"

//	This class represents the Dock, which when hovered over with the mouse, slides down to reveal all the widgets.
class Dock final : public Widget
{
private:

	// An enum class representing the different states of the dock: idle, going down, or going up
	enum class m_dock_status
	{
		STATE_IDLE,      // Dock is not being hovered or moving
		STATE_GOING_DOWN,// Dock is being hovered and is sliding down
		STATE_GOING_UP   // Dock was previously hovered and is sliding up
	};

	// The height and width of the dock
	const float m_dock_height{ CanvasConst::CANVAS_HEIGHT / 2 };
	const float m_dock_width{ CanvasConst::CANVAS_WIDTH / 2 };

	// The current state of the dock, initialized to "IDLE"
	m_dock_status m_dock_state{ m_dock_status::STATE_IDLE };

	// The offset used when the dock is sliding down to extend the area where the mouse can be
	float m_offset{ -15.0f };

	// A boolean variable to play the sound of the dock sliding only once
	bool PlaySound{ true };

	// A vector containing all the widgets (excluding the Dock itself)
	std::vector<Widget*> widgets;

private:

	// Checks if the mouse is within the boundaries of the dock
	// @param mouse_x: the x-coordinate of the mouse
	// @param mouse_y: the y-coordinate of the mouse
	// @return true if the mouse is within the dock's boundaries, false otherwise
	bool contains(float mouse_x, float mouse_y) const;

	// Sets all movies as not updatable/or updatables using the `movie_list` when the dock is hovered and is sliding down or up, 
	// also sets visibility true/false whether the dock is going down/up
	// @param movie_list: a vector of all the movies to be filtered
	void takeAction(const std::vector<Movie*>& movie_list) override;

	// Resets the dock's state
	void clear() override;

	// Sets the x-coordinate of the dock's position
	void setPosX(float x) { m_positionX = x; }

	// Sets the y-coordinate of the dock's position
	void setPosY(float y) { m_positionY = y; }

	void setOffset(float off) { m_offset = off; }

public:

	//Function that continuously updates our dock
	void update() override;

	//Function that continuously draws our dock
	void draw() override;

	//Constructs a new Dock
	//   @param float x: The x-coordinate of the dock's position.
	//   @param float y: The y-coordinate of the dock's position.
	//   @param const std::vector<Widget*>& widgets_list: A reference to a vector of pointers to Widget objects.
	Dock(float x, float y, const std::vector<Widget*>& widgets_list);

};

#endif