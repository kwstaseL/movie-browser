#include "GUI.h"
#include <math.h>
#include <iostream>

/*

Note-> First GUI Draw is called and then GUI update by message loop

*/


//Updating Loading Screen
void GUI::updateLoadingScreen() const
{
}

//Updating Start Screen
void GUI::updateStartScreen() const
{
	//For every movie and for our dock, update its state

	for (auto& movie : movie_list)
	{

		if (movie)
		{
			if (!movie->isDisabled())
			{
				movie->update();		//Updating our movies
			}
			else
			{
				// ?
			}
			
		}

		if (dock->isPressed() && dock)
		{
			movie->setActive(false);
		}
		else
		{
			movie->setActive(true);
		}

	}

	if (dock)
	{
		dock->update();	//Updating our dock
	}

	for (const auto& widget : widgets)	//Polymorphism
	{
		widget->update();

		if (widget->actionTriggered() &&  !widget->isOperating())
		{
			widget->setOperating(true);
			widget->takeAction(movie_list);

		}
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

	for (const auto& movie : movie_list)
	{
		if (movie)
		{
			if (!movie->isDisabled())
			{
				movie->draw();
			}
			else 
			{
				// ?
			}
		}
	}

	if (dock)
	{
		dock->draw();
	}


	for (const auto& widget : widgets)	//Polymorphism
	{
		widget->draw();

	}

}


void GUI::init()
{
	graphics::setFont("FreeSans.ttf");
	CreateDock();
	CreateMovies();	//Creating our Movies
	CreateWidgets();

	graphics::preloadBitmaps(AssetsConst::ASSET_PATH);

}

void GUI::CreateDock()
{

	dock = new Dock();
	dock->setPosX(CanvasConst::CANVAS_WIDTH / 2);
	dock->setPosY(CanvasConst::CANVAS_HEIGHT / 2);

}

void GUI::CreateWidgets()
{

	widgets.push_back(new Button(CanvasConst::CANVAS_WIDTH / 15 + 7.0f, CanvasConst::CANVAS_HEIGHT / 1.28, "Action"));
	widgets.push_back(new Button(CanvasConst::CANVAS_WIDTH / 15 + 15.0f, CanvasConst::CANVAS_HEIGHT / 1.28, "Drama"));
	widgets.push_back(new Button(CanvasConst::CANVAS_WIDTH / 15 + 20.0f, CanvasConst::CANVAS_HEIGHT / 1.28, "Horror"));

}



void GUI::CreateMovies()
{

	//Creating our 9 movies.

	movie_list.push_back(new Movie("Harry Potter", "This is desc", "This is age", AssetsConst::HARRY_POTTER, "2004", "Chris Columbus", "Daniel Radcliffe", { "Adventure","Fantasy"}));
	movie_list.push_back(new Movie("GodFather", "This is desc", "This is age", AssetsConst::GODFATHER, "1972", "The director", "The protagonist", { "Crime","Drama"}));
	movie_list.push_back(new Movie("Terminator", "This is desc", "This is age", AssetsConst::TERMINATOR, "1984", "The director", "The protagonist", { "Action","Sci-Fi","Drama"}));
	movie_list.push_back(new Movie("A New Hope", "This is desc", "This is age", AssetsConst::ANEWHOPE, "1997", "The director", "The protagonist", { "Action","Adventure","Fantasy"}));
	movie_list.push_back(new Movie("Schindlers List", "This is desc", "This is age", AssetsConst::SCHINDLERSLIST, "1994", "The director", "The protagonist", { "Drama","History"}));
	movie_list.push_back(new Movie("The Chronicles Of Narnia", "This is desc", "This is age", AssetsConst::NARNIA, "1984", "The director", "The protagonist", { "Adventure","Fantasy" }));
	movie_list.push_back(new Movie("Home Alone", "This is desc", "This is age", AssetsConst::HOMEALONE, "1980", "The director", "The protagonist", { "Comedy" , "Family"}));
	movie_list.push_back(new Movie("Pulp Fiction", "This is desc", "This is age", AssetsConst::PULPFICTION, "1995", "The director", "The protagonist", { "Crime", "Drama"}));
	movie_list.push_back(new Movie("MidSommar", "This is desc", "This is age", AssetsConst::MIDSOMMAR, "1995", "The director", "The protagonist", { "Horror","Mystery"}));
	movie_list.push_back(new Movie("The Invisible Man", "This is desc", "This is age", AssetsConst::THEINVISIBLEMAN, "1995", "The director", "The protagonist", { "Horror", "Sci-Fi"}));



	size_t size = movie_list.size();
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j <= 4; j++)
		{

			movie_list[j + (i * 3 + i * 1 + i*1)]->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - i * 6.3)));
			movie_list[j + (i * 3 + i * 1 + i*1)]->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + j * 5.5);
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
	for (const auto& movie : movie_list)
	{
		delete movie;
	}
	if (dock)
	{
		delete dock;
	}

	for (const auto& widget : widgets)
	{
		delete widget;
	}

	dock = nullptr;
	movie_list.clear();		//Clearing out our movie vector
	widgets.clear();

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
