#ifndef FILTER_GENRE_BUTTON_H
#define FILTER_GENRE_BUTTON_H

#include "Button.h"

class FilterGenreButton final : public Button
{
private:

	using genreMap = std::unordered_map<std::string, std::unordered_set<Movie*>>;

private:

	static inline genreMap s_genreMap;

	static inline bool genreMapCreated{ false };

	bool hasAtLeastOneGenre{ false };

	bool hasRequirements(const Movie* movie) const;

	void filterByGenre(const std::vector<Movie*>& movie_list);

	void createGenreMap(const std::vector<Movie*>& movie_list);

	void setGenreMapCreated(bool a) { genreMapCreated = a; }
	bool isGenreMapCreated() const { return genreMapCreated; }

	void takeAction(const std::vector<Movie*>& movie_list) override;

	void update() override;
	void draw() override;

public:

	FilterGenreButton(float posX, float posY, const std::string_view text);
	virtual ~FilterGenreButton() = default;

};




#endif