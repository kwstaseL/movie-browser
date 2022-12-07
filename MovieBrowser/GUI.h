#ifndef  GUI_H
#define GUI_H

#include <vector>
#include "Movie.h"
#include "Dock.h"


class GUI
{

public:

	enum gui_state_t {

		STATUS_LOADING,
		STATUS_LOADED

	};

private:

	//Marking constructor and copy constructor as private so we only make 1 instance of our class
	graphics::Brush br;
	GUI() {}
	GUI(const GUI& other) = delete;

	gui_state_t m_state{STATUS_LOADED};

	static GUI* gui;

	Dock* dock{ nullptr };
	std::vector<Movie*> movie_list;	//Here we keep all our movies

	void CreateMovies();
	void CreateDock();
	~GUI();
	void updateLoadingScreen();
	void updateStartScreen();
	void drawLoadingScreen();
	void drawStartScreen();


public:

	void draw();
	void init();
	void update();
	static GUI* Get();
	static void releaseInstance();



};

#endif
