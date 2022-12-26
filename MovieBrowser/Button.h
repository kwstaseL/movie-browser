#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include <unordered_set>


class Button : public Widget
{
protected:

	enum class button_state_t {

		BUTTON_IDLE,
		BUTTON_PRESSED,
		BUTTON_HIGHLIGHTED

	};

	std::string m_button_text{};

	const float m_Genrebutton_height{ .5f };
	const float m_Genrebutton_width{ 3.0f };

	button_state_t m_button_state{ button_state_t::BUTTON_IDLE };

	static inline std::unordered_set<std::string> s_scanned_genres;

	float m_height{ 0.0f };

	bool contains(float x, float y) const;

private:

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

public:

	Button(float posX, float posY, const std::string_view text);
	virtual ~Button() = default;

};



#endif









