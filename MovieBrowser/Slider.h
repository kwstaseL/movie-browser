#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "Widget.h"

//DONE

struct ClickableBox
{
private:

	float m_positionX{};
	float m_positionY{};

	bool m_active{ false };

public:

	bool isActive() const { return m_active; }
	int getPosX() const { return m_positionX; }
	int getPosY() const { return m_positionY; }
	
	void setPosX(int x) { m_positionX = x; }
	void setPosY(int y) { m_positionY = y; }
	void setActive(bool a) { m_active = a; }


};

class Slider : public Widget
{
private:

	enum m_slider_state
	{
		SLIDER_IDLE,
		SLIDER_RELEASED,
		SLIDER_DRAGGING
	};
	
	const std::string m_text;

	float m_height{ 0.0f };

	m_slider_state m_status_slider{ SLIDER_IDLE };

	ClickableBox box;

	int m_year{};

	void update() override;

	void draw() override;

	bool contains(float x, float y) const;

	void takeAction(const std::vector<Movie*>& movie_list) override;

	void filterByYear(const std::vector<Movie*>& movie_list);



public:

	void clearSlider();
	Slider(float posX, float posY, const std::string_view text);
	virtual ~Slider() = default;

};










#endif