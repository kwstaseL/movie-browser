#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Widget.h"


class TextField : public Widget
{
private:

	const float m_Textfield_height{ 0.5f };
	const float m_Textfield_width{ 4.0f };

	bool m_typed{ false };

	bool hasRequirements(const Movie* movie) const;

	int m_counter{ -1 };

	const std::string m_text;

	bool textInvisible{ false };

	void searchByTitle(const std::vector<Movie*>& movie_list);

	float m_height{ 0.0f };
	std::vector<char> characters;

public:

	void draw() override;
	void update() override;

	void takeAction(const std::vector<Movie*>& movie_list) override;

	bool contains(float x, float y) const;

	void deleteText();

	TextField(float posX, float posY, const std::string_view text);
};


#endif	
