#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Widget.h"

/*struct TextBox
{
private:
	float m_positionX{};
	float m_positionY{};
	bool m_active{ false };
	bool m_pressed{ false };
public:
	float getPosX() const { return m_positionX; }
	float setPosX(float x) { m_positionX = x; }
	float getPosY() const { return m_positionY; }
	float setPosY(float y) { m_positionY = y; }
	bool getActive() const { return m_active; }
	bool setActive(bool active) { m_active = m_active; }
}; */

class TextField final : public Widget
{
private:


	bool m_active{ false };
	bool m_pressed{ false };
	bool m_typed{ false };
	int m_counter{ 0 };
	const std::string m_text;
	float m_height{ 0.0f };
	std::vector<char> characters;
	int iterator{ 0 };

public:

	void draw() override;
	void update() override;

	void takeAction(const std::vector<Movie*>& movie_list) override;

	bool contains(float x, float y) const;

	float getPosX() const { return m_positionX; }
	float setPosX(float x) { m_positionX = x; }

	float getPosY() const { return m_positionY; }
	float setPosY(float y) { m_positionY = y; }

	bool getActive() const { return m_active; }
	bool setActive(bool active) { m_active = m_active; }

	void deleteText();

	TextField(float posX, float posY, const std::string_view text);
};


#endif