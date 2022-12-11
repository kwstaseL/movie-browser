#ifndef  GUI_H
#define GUI_H

#include <vector>
#include "Movie.h"
#include "Dock.h"
#include "Widget.h"
#include "Button.h"

class GUI
{
private:
	
	enum gui_state_t
	{
		STATUS_LOADING,
		STATUS_LOADED
	};

	//Marking constructor and copy constructor as private so we only make 1 instance of our class
	graphics::Brush br;
	GUI() {}
	GUI(const GUI& other) = delete;

	gui_state_t m_state{STATUS_LOADED};

	static GUI* gui;

	Dock* dock{ nullptr };
	std::vector<Movie*> movie_list;	//Here we keep all our movies
	std::vector<Widget*> widgets;

	void CreateMovies();
	void CreateDock();
	void CreateWidgets();

	~GUI();
	void updateLoadingScreen() const;
	void updateStartScreen() const;
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
