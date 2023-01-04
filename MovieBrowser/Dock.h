#ifndef DOCK_H
#define DOCK_H

#include "Widget.h"

class Dock final : public Widget
{
private:

	//Keeping all states of our dock

	enum class m_dock_status
	{
		STATE_IDLE,
		STATE_GOING_DOWN,
		STATE_GOING_UP
	};

	m_dock_status m_dock_state{ m_dock_status::STATE_IDLE };

	float m_offset{ -15.0f };	//Offset used to 

	bool PlaySound{ true };

	std::vector<Widget*> widgets;	//Saving all the widgets

private:

	bool contains(float x, float y) const;		 
	void setOffset(float off) { m_offset = off; }
	void takeAction(const std::vector<Movie*>& movie_list) override;
	void clear() override;
	void setPosX(float x) { m_positionX = x; }
	void setPosY(float y) { m_positionY = y; }

public:

	void update() override;
	void draw() override;

	Dock(float x, float y, const std::vector<Widget*>& widgets_list);
};



#endif