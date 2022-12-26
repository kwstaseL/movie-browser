#ifndef WIDGET_H
#define WIDGET_H

#include "Movie.h"

class Widget
{
private:

	static inline int s_idGenerator{};

protected:

	float mouse_X{};
	float mouse_Y{};

	float m_positionX{};
	float m_positionY{};

	bool m_highlighted{ false };
	bool operating{ false };
	bool m_visible{ false };
	bool m_action{ false };

	static inline int s_focus{};
	int m_uid{};

	bool requestFocus();
	void releaseFocus();

	graphics::Brush brush;

public:

	void setActionTriggered(bool action) { m_action = action; }

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual bool isOperating() const { return operating; }
	virtual void setOperating(bool o) { operating = o; }

	virtual bool actionTriggered() const { return m_action; }

	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

	virtual int getID() const { return m_uid; }

	virtual void setVisibility(bool v) { m_visible = v; }

	Widget(float posX, float posY);
	virtual ~Widget();
};



#endif





