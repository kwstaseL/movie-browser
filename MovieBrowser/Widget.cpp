#include "Widget.h"

void Widget::releaseFocus()
{
	if (s_focus == m_uid)
	{
		s_focus = 0;
	}
}

bool Widget::requestFocus()
{
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