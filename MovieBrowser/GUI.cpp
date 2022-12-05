#include "GUI.h"
#include <math.h>
#include <iostream>

/*

Note-> First GUI Draw is called and then GUI update by message loop

*/

void GUI::init()
{
	graphics::setFont("FreeSans.ttf");

	CreateDock();
	CreateMovies();	//Creating our Movies

	graphics::preloadBitmaps(AssetsConst::ASSET_PATH);

}

void GUI::CreateDock()
{

	dock = new Dock();
	dock->setPosX(CanvasConst::CANVAS_WIDTH / 2);
	dock->setPosY(CanvasConst::CANVAS_HEIGHT / 2);

}



void GUI::CreateMovies()
{
	//Creating our movies.

	Movie* movie1{ new Movie("Harry Potter", "A skirmish in Shanghai puts archaeologist Indiana Jones, his partner Short Round and singer Willie Scott crossing paths with an Indian village desperate to reclaim a rock stolen by a secret cult beneath the catacombs of an ancient palace.", "This is age",AssetsConst::HARRY_POTTER) };
	Movie* movie2{ new Movie("GodFather", "This is desc", "This is age", AssetsConst::GODFATHER) };
	Movie* movie3{ new Movie("Terminator", "This is desc", "This is age", AssetsConst::TERMINATOR) };
	Movie* movie4{ new Movie("A New Hope", "This is desc", "This is age", AssetsConst::ANEWHOPE) };
	Movie* movie5{ new Movie("Schindlers List", "This is desc", "This is age", AssetsConst::SCHINDLERSLIST) };
	Movie* movie6{ new Movie("Temple Of Doom", "This is desc", "This is age", AssetsConst::TEMPLEOFDOOM) };
	Movie* movie7{ new Movie("Empire Strikes Back", "This is desc", "This is age", AssetsConst::EMPIRESTRIKESBACK) };
	Movie* movie8{ new Movie("Pulp Fiction", "This is desc", "This is age", AssetsConst::PULPFICTION) };


	//Put them in a vector

	movie_list.push_back(movie1);
	movie_list.push_back(movie2);
	movie_list.push_back(movie3);
	movie_list.push_back(movie4);
	movie_list.push_back(movie5);
	movie_list.push_back(movie6);
	movie_list.push_back(movie7);
	movie_list.push_back(movie8);



	size_t size = movie_list.size();
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j <= 4; j++)
		{

			movie_list[j + (i * 2 + i * 1)]->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - i * 6.3)));
			movie_list[j + (i * 2 + i * 1)]->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + j * 5);

			size--;

		}
	}
}


void GUI::draw()	//Drawing of all our classes
{
	if (m_state == STATUS_LOADING)
	{
		drawLoadingScreen();
	}
	else
	{
		drawStartScreen();
	}
	

}


void GUI::update()	//Updating of all our classes
{
	if (m_state == STATUS_LOADING)
	{
		updateLoadingScreen();
	}
	else
	{
		updateStartScreen();
	}

}


GUI::~GUI()
{
	for (auto& movie : movie_list)
	{
		delete movie;
	}
	if (dock)
	{
		delete dock;
	}
	dock = nullptr;
	movie_list.clear();		//Clearing out our movie vector

}

GUI* GUI::Get()		//Here we set it as static so we can use it without the need of an existing object, if there is no instance of gui made yet, make one and return it
					//So the next time get gets called, it won't make another instance and just return the existing one
{
	if (!gui)
	{
		gui = new GUI() ;
	}
	return gui;

}

void GUI::releaseInstance() //Delete object
{
	if (gui)
	{
		delete gui;
	}
	gui = nullptr;
}

//Updating Loading Screen
void GUI::updateLoadingScreen()
{
}

//Updating Start Screen
void GUI::updateStartScreen()
{

	for (auto& item : movie_list)
	{
		if (item)
		{
			item->update();		//Updating our movies
		}
	}

	if (dock)
	{
		dock->update();	//Updating our dock
	}
}


//Drawing Loading Screen
void GUI::drawLoadingScreen()
{
}


//Actual GUI drawing
void GUI::drawStartScreen()
{
	//Background
	br.fill_opacity = 0.5f;
	br.outline_opacity = 0.0f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::BACKGROUND);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT, br);


	for (auto& item : movie_list)
	{
		if (item)
		{
			item->draw();
		}
	}

	//Dock

	if (dock)
	{
		dock->draw();
	}
}


GUI* GUI::gui{}; //Because its static we need to initialize it 