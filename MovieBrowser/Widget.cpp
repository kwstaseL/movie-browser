#include "Widget.h"

void Widget::releaseFocus()
{
	//If i have the focus, then only me can release it
	if (s_focus == m_uid)
	{
		s_focus = 0;
	}
}

//Requesting focus in order to do a specific task
bool Widget::requestFocus()
{	
	//If no one is operating currently, only then I can operate
	if (!s_focus || s_focus == m_uid)
	{
		s_focus = m_uid;
		return true;
	}

	return false;
}

Widget::~Widget() = default;

Widget::Widget(float posX, float posY)
	: m_positionX{ posX }, m_positionY{ posY }, m_uid{ s_idGenerator++ }
{
}