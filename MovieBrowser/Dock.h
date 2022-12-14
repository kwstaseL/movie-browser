#ifndef DOCK_H
#define DOCK_H

#include "constants.h"
#include "sgg/graphics.h"

//DONE

class Dock
{
private:

	enum dock_state_t
	{
		STATE_IDLE,
		STATE_DRAWING,
		STATE_MOVING_TRIGGERED

	};

	float m_posX{};
	float m_posY{};
	float height{ 0.0f };
	float m_offset{ -15.0f };
	bool PlaySound{ true };
	bool Pressed{ false };
	dock_state_t m_current_state = STATE_DRAWING;

private:

	bool contains(float x, float y) const;
	void setOffset(float off) { m_offset = off; }

public:

	void update();
	void draw() const;
	void setPosX(float x) { m_posX = x; }
	void setPosY(float y) { m_posY = y; }
	bool isPressed() const { return Pressed; }

};



#endif