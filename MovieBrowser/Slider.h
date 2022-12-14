#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "Widget.h"

//DONE

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

	Box ClickableBox;

	int m_year{ 1950 };

	void update() override;
	void draw() override;

	bool contains(float x, float y) const;

	void takeAction(const std::vector<Movie*>& movie_list) override;


public:

	Slider(float posX, float posY, const std::string_view text);
	virtual ~Slider() = default;
	void resetSlider();

};










#endif