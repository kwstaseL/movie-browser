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



bool Widget::isOperating()
{
	return false;
}

Widget::Widget(float posX, float posY)
	: m_positionX{posX}, m_positionY{ posY }, m_uid{ s_idGenerator++ }
{
}


//int Widget::m_next_id = 0;
std::vector<std::string> Widget::m_scanned_genres;


//Change m->s on static members