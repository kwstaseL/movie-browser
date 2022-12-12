#include "Widget.h"


void Widget::releaseFocus()
{
	//If I had the focus then I MUST release it
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

Widget::~Widget()
{}



Widget::Widget(float posX, float posY)
	: m_positionX{posX}, m_positionY{ posY }, m_uid{ s_idGenerator++ }
{
}