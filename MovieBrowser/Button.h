#ifndef BUTTON_H
#define BUTTON_h

#include "Widget.h"

class Button : public Widget
{
private:
	enum button_state_t {
		BUTTON_IDLE,
		BUTTON_PRESSED,
		BUTTON_HIGHLIGHTED
	};

	std::string m_button_text{};

	graphics::Brush brush;

	const float m_Genrebutton_height{ 1.0f };
	const float m_Genrebutton_width{ 3.0f };

	button_state_t m_button_state = BUTTON_IDLE;

	float m_cur_pos_x{};
	float m_cur_pos_y{};

private:

	void update() override;
	void draw() override;

	bool contains(float x, float y) const;

	void filterByGenre(const std::vector<Movie*>& movie_list) const;
	void resetFilter(const std::vector<Movie*>& movie_list) const;

	void takeAction(const std::vector<Movie*>& movie_list) override;



public:

	Button(float posX, float posY, const std::string& text);

};




/*

	When you done with Filters

	Make just 1 Button class

	play with id's
	if i have 8 buttons for genre then:

		- Make a takeAction
			if (id>=0 && id<=7)
				call filterByGenres()
			if (id == 8)
				call resetFilter




*/
	

#endif










