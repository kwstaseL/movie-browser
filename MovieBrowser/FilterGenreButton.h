#ifndef FILTER_GENRE_BUTTON_H
#define FILTER_GENRE_BUTTON_H

#include "Button.h"


/*
	Represents a FilterGenreButton, which in our program has a text ("Action","Drama"), and when pressed filters movies by that text.
	The FilterGenreButton class is derived from the Button class, which provides a common interface for interacting with different types of Buttons.
	When filtering, we also take as consideration all the other widgets that may have filtered the movies.
*/
class FilterGenreButton final : public Button
{
private:

	using genreMap = std::unordered_map<std::string, std::unordered_set<Movie*>>;

private:

	// A map in which the key is a genre text ("Action","Drama"...) and the value is an unordered set of all the movies that have that specific genre.
	// This map is used to quickly filter movies by genre.
	static inline genreMap s_genreMap;

	// A flag indicating whether the genre map has been created (only created once)
	static inline bool genreMapCreated{ false };

	// A flag indicating that there is at least one movie with multiple combinations of genres.
	// For example, if the "Action" and "Drama" buttons are pressed and there is at least one movie
	// that has both the Action and Drama genres, this variable would be true.
	bool atLeastOneMovieHasGenres{ false };

	// A set of genre buttons that have been pressed, stored by their names. It is static because every
	// filter genre button needs to know about it when filtering.
	static inline std::unordered_set<std::string> s_scanned_genres;

	/*
		Checks if the given movie meets the requirements for filtering, including the filtered text
		(if text was typed in the text field) and the years filtered by the slider.

		@param movie: a pointer to the movie to be checked
		@return true if the movie meets the requirements, false otherwise
	*/
	bool hasRequirements(const Movie* movie) const;

	// Filters all movies by genre
	// @param movie_list: a vector of all the movies to be filtered
	void filterByGenre(const std::vector<Movie*>& movie_list);

	/* Creates the genre map
	  @param movie_list: a vector of all the movies to be included in the genre map
	 The genre map is a mapping from genre names to sets of movies with that genre. It is used to quickly filter movies by genre.
	*/ 
	void createGenreMap(const std::vector<Movie*>& movie_list);

	// Sets the flag indicating whether the genre map has been created
	void setGenreMapCreated(bool a) { genreMapCreated = a; }

	// Returns the flag indicating whether the genre map has been created
	bool isGenreMapCreated() const { return genreMapCreated; }

	// Resets the state of the button
	void clear() override;

	// Performs the filtering action when the button is pressed
	// @param movie_list: a vector of all the movies to be filtered
	void takeAction(const std::vector<Movie*>& movie_list) override;

	// Updates the state of the filter genre button
	void update() override;

	// Draws all the filter genre buttons
	void draw() override;

public:

	/* Constructs a new filter genre button
	 @param posX: the x-coordinate of the button's position
	 @param posY: the y-coordinate of the button's position
	 @param text: the text displayed on the button
	*/
	FilterGenreButton(float posX, float posY, const std::string_view text);
	virtual ~FilterGenreButton() = default;

};




#endif