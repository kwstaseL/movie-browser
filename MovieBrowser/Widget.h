#pragma once

class Widget
{
private:

	int m_pos[2]{};

public:

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual ~Widget();

};










