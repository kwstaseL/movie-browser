#ifndef RESET_FILTER_BUTTON_H
#define RESET_FILTER_BUTTON_H

#include "Button.h"
#include "Slider.h"


class ResetFilterButton final : public Button
{
private:

	void resetFilter(const std::vector<Movie*>& movie_list) const;

	void takeAction(const std::vector<Movie*>& movie_list) override;

	void update() override;
	void draw() override;

public:

	ResetFilterButton(float posX, float posY, const std::string_view text);
	virtual ~ResetFilterButton() = default;
};




#endif