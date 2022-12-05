#pragma once

#include "constants.h"
#include "sgg\graphics.h"

class Dock
{
public:

	float m_posX;
	float m_posY;
	float height{ 0.0f };
	bool PlaySound{ true };

public:



	enum dock_state_t
	{
		STATE_IDLE,
		STATE_DRAWING,
		STATE_MOVING_TRIGGERED

	};

	dock_state_t m_current_state = STATE_DRAWING;

	void update();
	void draw() const;
	void setPosX(float x) { m_posX = x; }
	void setPosY(float y) { m_posY = y; }
	bool contains(float x, float y) const;


};



