#include "Event.h"
#include "sgg/graphics.h"

/*
void Event::update()
{

	if (!m_isEventActive)
	{
		return;
	}

	if (waiting())
	{
		m_elapsed_delay += graphics::getDeltaTime()/1000.0f;
		return;
	}

	m_elapsed_time += graphics::getDeltaTime() / 1000.0f;

	if (m_elapsed_time > m_duration)
	{
		m_isEventActive = false;
	}

}

Event::Event(const float& x, const float& y, const float& dur, const float& delay)
	: m_pos_x(x), m_pos_y(y), m_duration(dur),m_delay(delay)
{
}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}
*/