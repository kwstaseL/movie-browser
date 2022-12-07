#include "GUI.h"
#include <math.h>
#include <iostream>

/*

Note-> First GUI Draw is called and then GUI update by message loop

*/


//Updating Loading Screen
void GUI::updateLoadingScreen()
{
}

//Updating Start Screen
void GUI::updateStartScreen()
{
	//For every movie and for our dock, update its state

	for (auto& movie : movie_list)
	{
		if (movie)
		{
			movie->update();		//Updating our movies
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

	//For every movie and for our dock, draw it

	for (auto& movie : movie_list)
	{
		if (movie)
		{
			movie->draw();
		}
	}


	if (dock)
	{
		dock->draw();
	}
}


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

	//Creating our 9 movies.

	movie_list.push_back(new Movie("Harry Potter", "This is desc", "This is age", AssetsConst::HARRY_POTTER, "4/5/2004", "Chris Columbus", "Daniel Radcliffe", "Fantasy"));
	movie_list.push_back(new Movie("GodFather", "This is desc", "This is age", AssetsConst::GODFATHER, "15/3/1972", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("Terminator", "This is desc", "This is age", AssetsConst::TERMINATOR, "26/10/1984", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("A New Hope", "This is desc", "This is age", AssetsConst::ANEWHOPE, "28/3/1997", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("Schindlers List", "This is desc", "This is age", AssetsConst::SCHINDLERSLIST, "2/3/1994", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("Temple Of Doom", "This is desc", "This is age", AssetsConst::TEMPLEOFDOOM, "8/5/1984", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("Empire Strikes Back", "This is desc", "This is age", AssetsConst::EMPIRESTRIKESBACK, "19/12/1980", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("Pulp Fiction", "This is desc", "This is age", AssetsConst::PULPFICTION, "1/5/1995", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("MidSommar", "This is desc", "This is age", AssetsConst::MIDSOMMAR, "1/5/1995", "The director", "The protagonist", "The genre"));
	movie_list.push_back(new Movie("The Invisible Man", "This is desc", "This is age", AssetsConst::THEINVISIBLEMAN, "1/5/1995", "The director", "The protagonist", "The genre"));



	size_t size = movie_list.size();
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j <= 4; j++)
		{

			movie_list[j + (i * 3 + i * 1 + i*1)]->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - i * 6.3)));
			movie_list[j + (i * 3 + i * 1 + i*1)]->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + j * 5.5);
			std::cout << "J = " << j + (i * 3 + i * 1 + i*1) << std::endl;
			size--;
			if (j + (i * 3 + i * 1 + i * 1) == 7)
			{
				break;
			}

		}
	}
	movie_list[8]->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + 3 * 5.5);
	movie_list[8]->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - 1 * 6.3)));

	movie_list[9]->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + 4 * 5.5);
	movie_list[9]->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - 1 * 6.3)));

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
		gui = new GUI();
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



GUI* GUI::gui{}; //Because its static we need to initialize it 
