#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Widget.h"


class TextField final : public Widget
{
private:

	bool m_typed{ false };

	bool hasRequirements(const Movie* movie) const;

	int m_counter{ -1 };

	const std::string m_text;

	bool textInvisible{false};

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