#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Widget.h"

class TextField final : public Widget
{
private:




public:

	void draw() override;
	void update() override;

	void takeAction(const std::vector<Movie*>& movie_list) override;

};













#endif