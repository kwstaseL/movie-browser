#ifndef FILTER_GENRE_BUTTON_H
#define FILTER_GENRE_BUTTON_H

#include "Button.h"

class FilterGenreButton final : public Button
{
private:

	using genreMap = std::unordered_map<std::string, std::unordered_set<Movie*>>;

private:

	//An unordered map in which the key is a genre text ("Action","Drama"...) and the result is an unordered set which contains all the movies that have that specific genre
	static inline genreMap s_genreMap;

	//Variable which shows if genreMap is Created , so we only create it 1 time
	static inline bool genreMapCreated{ false };

	//Indicates if the filter button that we pressed, 
	bool hasAtLeastOneGenre{ false };

	//This stores every genre button that is pressed,its static because every button needs to know about it
	static inline std::unordered_set<std::string> s_scanned_genres;

	//Checking if the movie that we pressed has
	bool hasRequirements(const Movie* movie) const;

	//Filters all movies by genre
	//Input: a vector of all our movies
	void filterByGenre(const std::vector<Movie*>& movie_list);

	//Creates the genre map
	//Input: a vector of all our movies
	void createGenreMap(const std::vector<Movie*>& movie_list);

	void setGenreMapCreated(bool a) { genreMapCreated = a; }
	bool isGenreMapCreated() const { return genreMapCreated; }

	void clear() override;

	//Function that is called when the button is pressed
	void takeAction(const std::vector<Movie*>& movie_list) override;

	//Updating filter genre button state
	void update() override;

	//Drawing every filter genre button
	void draw() override;

public:

	FilterGenreButton(float posX, float posY, const std::string_view text);
	virtual ~FilterGenreButton() = default;

};




#endif