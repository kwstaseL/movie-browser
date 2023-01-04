#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Widget.h"
#include <stack>
#include <deque>


class TextField : public Widget
{
private:

	const float m_Textfield_height{ 0.5f };
	const float m_Textfield_width{ 4.0f };

	bool m_typed{ false };

	bool hasRequirements(const Movie* movie) const;

	int m_counter{ -1 };
	
	std::stack<char> outofsight_words;

	const std::string m_text;

	int extra_words{ 0 };

	bool isFull{ false };

	bool textInvisible{ false };

	void searchByTitle(const std::vector<Movie*>& movie_list);
	void clear() override;

	bool contains(float x, float y) const;
	void takeAction(const std::vector<Movie*>& movie_list) override;



	std::deque<char> characters;

public:

	void draw() override;
	void update() override;

	TextField(float posX, float posY, const std::string_view text);
};


#endif	