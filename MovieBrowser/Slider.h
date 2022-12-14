#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "Widget.h"

//DONE

struct ClickableBox
{
private:

	static inline float m_positionX{};
	static inline float m_positionY{};

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

	static inline ClickableBox box;

	static inline int m_year{ 1950 };

	void update() override;
	void draw() override;

	bool contains(float x, float y) const;

	void takeAction(const std::vector<Movie*>& movie_list) override;


public:

	Slider(float posX, float posY, const std::string_view text);
	virtual ~Slider() = default;

	static void resetSlider()
	{
		box.setPosX(CanvasConst::CANVAS_WIDTH / 15 + 11.5f - 2.9f);
		m_year = 1950;
	}

};










#endif