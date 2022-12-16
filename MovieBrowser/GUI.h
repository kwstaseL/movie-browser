#ifndef GUI_H
#define GUI_H

#include "Movie.h"
#include "Dock.h"
#include "Widget.h"
#include "ResetFilterButton.h"
#include "FilterGenreButton.h"
#include "Slider.h"


class GUI
{
private:
	
	enum gui_state_t
	{
		STATUS_LOADING,
		STATUS_STARTED,
		STATUS_MOVIE_PRESSED
	};

	gui_state_t m_state{ STATUS_STARTED };

	graphics::Brush br;

	Widget* lastActiveWidget;

	GUI() {};
	GUI(const GUI& other) = delete;
	GUI& operator=(const GUI&) = delete;

	static inline GUI* s_gui{};

	Movie* clickedMovie{ nullptr };

	Dock* dock{ nullptr };

	std::vector<Movie*> movie_list;
	std::vector<Widget*> widgets;

	void CreateMovies();
	void CreateDock();
	void CreateWidgets();

	~GUI();
	void updateLoadingScreen() const;
	void drawLoadingScreen();

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
