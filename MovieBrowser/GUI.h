#ifndef GUI_H
#define GUI_H

#include "Movie.h"
#include "Dock.h"
#include "Widget.h"
#include "ResetFilterButton.h"
#include "FilterGenreButton.h"
#include "Slider.h"
#include "TextField.h"


class GUI
{
private:
	/* Enum represents all the states our programs goes to
	* 
	* - STATUS_STARTED indicates the starting screen where all movies are shown
	* - STATUS_MOVIE_PRESSED indicates the scene where a movie is pressed and all information is displayed about that specific movie
	* 
	*/
	enum gui_state_t
	{
		STATUS_STARTED,
		STATUS_MOVIE_PRESSED
	};

	gui_state_t m_state{ STATUS_STARTED };

	graphics::Brush br;

	Widget* lastActiveWidget;	//Indicates the last Widget being pressed/active

	GUI() {};

	//Because we use are using a Singleton we don't want to instantiate/copy another GUI instance
	GUI(const GUI& other) = delete;
	GUI& operator=(const GUI&) = delete;

	static inline GUI* s_gui{};	//Singleton instance of GUI

	Movie* clickedMovie{ nullptr };	//Indicates which movie was "clicked"

	std::vector<Movie*> movie_list;	//A vector which contains all movie pointers
	std::vector<Widget*> widgets;	//A vector which contains all widget pointers

	void CreateMovies();	//A function that creates all the movies
	void CreateWidgets();	//A function that creates all the widgets

	~GUI();
	void updateStartedScreen();
	void drawStartedScreen();

	void updatePressedMovieScreen();
	void drawPressedMovieScreen();

public:

	void draw();
	void update();

	void init();
	static GUI* Get();
	static void releaseInstance();

};

#endif