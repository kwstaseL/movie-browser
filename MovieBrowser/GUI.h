#ifndef GUI_H
#define GUI_H

#include "Movie.h"
#include "Dock.h"
#include "Widget.h"
#include "ResetFilterButton.h"
#include "FilterGenreButton.h"
#include "Slider.h"
#include "TextField.h"


/*
*	Represents the class where all our objects get updated and drawen.
*	This is the main class that knows and runs everything.
*/
class GUI
{
private:

	/* Enum represents all the states our programs goes to
	* 
	* - STATUS_STARTED indicates the starting screen where all movies are shown
	* - STATUS_MOVIE_PRESSED indicates the scene where a movie is pressed and all information is displayed about that specific movie
	*/
	enum gui_state_t
	{
		STATUS_STARTED,	
		STATUS_MOVIE_PRESSED
	};

	gui_state_t m_state{ STATUS_STARTED };

	// A vector which contains all movie pointers
	std::vector<Movie*> movie_list;

	// A vector which contains all widget pointers
	std::vector<Widget*> widgets;

	// Singleton instance of GUI
	static inline GUI* s_gui{};

	// Indicates which movie was "clicked"
	Movie* clickedMovie{ nullptr };

	//Indicates the last Widget being pressed/active
	Widget* lastActiveWidget{ nullptr };

	graphics::Brush br;

private:

	//A function that creates all the movies
	void CreateMovies();

	// A function that creates all the widgets
	void CreateWidgets();

	// Updates the started screen (the screen with all movies and widgets are shown)
	void updateStartedScreen();

	// Draws the started screen (the screen with all movies and widgets are shown)
	void drawStartedScreen();

	// Updates the pressed movie screen (where information about 1 movie is shown)
	void updatePressedMovieScreen();

	// Draws the pressed movie screen (where information about 1 movie is shown)
	void drawPressedMovieScreen();

	GUI() {};

	// Destroys all our objects
	~GUI();

	//Because we use are using a Singleton we don't want to instantiate/copy another GUI instance
	GUI(const GUI& other) = delete;
	GUI& operator=(const GUI&) = delete;

public:

	// Draw is the function that is continuously running and drawing all our objects to the screen.
	// - drawStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being drawned.
	// - drawPressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.
	void draw();

	// Update is the function that is continuously running and updating all our objects to the screen.
	// - updateStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being updated.
	// - updatePressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.
	void update();	

	// Function which initializes every object
	void init();

	// This method returns the instance of the GUI class. If an instance does not already exist, it creates a new one.
	static GUI* Get();

	// Destroys the instance of GUI.
	static void releaseInstance();

};

#endif