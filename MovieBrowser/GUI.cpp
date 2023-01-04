#include "GUI.h"


/*
	Draw is the function that is continuously running and drawing all our objects to the screen.
	- drawStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being drawned.
	- drawPressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.
*/

void GUI::draw()
{
	if (m_state == STATUS_STARTED)
	{
		drawStartedScreen();
	}
	else if (m_state == STATUS_MOVIE_PRESSED)
	{
		drawPressedMovieScreen();
	}

} //DONE
/*
	Update is the function that is continuously running and updating all our objects to the screen.
	- updateStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being updated.
	- updatePressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.
*/

void GUI::update()	//Updating of all our classes
{
	if (m_state == STATUS_STARTED)
	{
		updateStartedScreen();
	}
	else if (m_state == STATUS_MOVIE_PRESSED)
	{
		updatePressedMovieScreen();
	}

} //DONE

/*
	Function which updates our starting screen
*/
void GUI::updateStartedScreen()
{
	//For every movie, if the movie is not disabled (from some widget when filtering) , update it.
	for (const auto& movie : movie_list)
	{
		if (movie && !movie->isDisabled())
		{
			movie->update();

			//If a particular movie is clicked, and our movie is active (which means that this movie is being updated), 
			//change the state and start the scene where this movie's info is displayed
			if (movie->isClickTriggered() && movie->isActive())
			{
				m_state = STATUS_MOVIE_PRESSED;
				clickedMovie = movie;
			}
		}
	}

	//For every widget run each update function.
	for (const auto& widget : widgets)
	{
		if (widget)
		{
			widget->update();

			//If for all widgets an action is triggered (a button is clicked, or text is typed in the textfield, or slider is being dragged) and
			//The current widget which action is triggered is not operating currently, 
			//We run a function called takeAction which takes as data all movies, and does something with that , depending on which widget is called (button,textfield..)

			if (widget->actionTriggered() && !widget->isOperating())
			{
				lastActiveWidget = widget;
				widget->setOperating(true);
				widget->takeAction(movie_list);
			}

			/*Checking if the last active widget was a clear "filter" widget(id == 11), so we can reset the sliders position, and the textfield message
			* We can distinguish every widget based on their id, when a widget is created, it gets an id from 0,1,2... based on when it was created
			* */
			if (lastActiveWidget && lastActiveWidget->getID() == 11)
			{
				for (const auto& w : widgets)
				{
					w->clear();
				}
				lastActiveWidget = nullptr;
			}

		}

	}

}

//Drawing our starting screen
void GUI::drawStartedScreen()
{
	//Drawing our Background
	br.fill_opacity = 0.5f;
	br.outline_opacity = 0.0f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::BACKGROUND);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT, br);


	//For each movie we call Movie's draw function
	for (const auto& movie : movie_list)
	{
		if (movie && !movie->isDisabled())
		{
			movie->draw();
		}
	}

	//For each widget we call polymorphically its draw function
	for (const auto& widget : widgets)
	{
		if (widget)
		{
			widget->draw();
		}

	}

}

//Drawing the scene when a movie is pressed
void GUI::drawPressedMovieScreen()
{
	if (clickedMovie)
	{
		clickedMovie->drawInformation();
	}
}	  //DONE

//Updating the scene when a movie is pressed
void GUI::updatePressedMovieScreen()
{
	if (clickedMovie)
	{
		clickedMovie->setActive(false);
		clickedMovie->update();

		//If user released the mouse, to the previous state
		if (!clickedMovie->isClickTriggered())
		{
			m_state = STATUS_STARTED;
			clickedMovie->setActive(true);
		}
	}

}

//Initializing all our objects (movies,widgets)
void GUI::init()
{
	graphics::setFont("OpenSans-Regular.ttf");
	CreateMovies();
	CreateWidgets();

	graphics::preloadBitmaps(AssetsConst::ASSET_PATH);

}

void GUI::CreateWidgets()
{
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 8.3f, CanvasConst::CANVAS_HEIGHT / 1.28 - 12.0f - 2.0f, "Action"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 11.4f, CanvasConst::CANVAS_HEIGHT / 1.28 - 12.0f - 2.0f, "Drama"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 14.5f, CanvasConst::CANVAS_HEIGHT / 1.28 - 12.0f - 2.0f, "Horror"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 8.3f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Adventure"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 11.4f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Fantasy"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 14.5f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Sci-Fi"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 8.3f, CanvasConst::CANVAS_HEIGHT / 1.13 - 12.0f - 2.0f, "History"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 11.4f, CanvasConst::CANVAS_HEIGHT / 1.13 - 12.0f - 2.0f, "Comedy"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 14.5f, CanvasConst::CANVAS_HEIGHT / 1.13 - 12.0f - 2.0f, "Crime"));

	widgets.push_back(new Slider(CanvasConst::CANVAS_WIDTH / 15 + 11.5f, CanvasConst::CANVAS_HEIGHT / 1.20 - 12.0f - 2.0f, "From"));

	widgets.push_back(new Slider(CanvasConst::CANVAS_WIDTH / 15 + 11.5f, CanvasConst::CANVAS_HEIGHT / 1.10 - 12.0f - 2.0f, "To"));


	widgets.push_back(new ResetFilterButton(CanvasConst::CANVAS_WIDTH / 15 + 18.0f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Clear Filter"));

	widgets.push_back(new TextField(CanvasConst::CANVAS_WIDTH / 15 + 17.6f, CanvasConst::CANVAS_HEIGHT / 1.15f - 12.0f - 2.0f, "Search  Movie"));

	widgets.push_back(new Dock(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, widgets));
}

void GUI::CreateMovies()
{

	movie_list.push_back(new Movie("Harry Potter and the Goblet Of Fire", "Harry Potter finds himself competing in a hazardous tournament between rival schools of magic, but he is distracted by recurring nightmares.", AssetsConst::HARRY_POTTER, "2004", "Chris Columbus", { "Daniel Radcliffe","Rupert Grint","Richard Harris" }, { "Adventure", "Fantasy" }));
	movie_list.push_back(new Movie("The Godfather", "The aging patriarch of an organized crime dynasty in postwar New York City transfers control of his clandestine empire to his reluctant youngest son.", AssetsConst::GODFATHER, "1972", "Francis Ford Coppola", { "Marlon Brando", "Al Pacino", "James Caan" }, { "Crime","Drama" }));
	movie_list.push_back(new Movie("Terminator", "A human soldier is sent from 2029 to 1984 to stop an almost indestructible cyborg killing machine, sent from the same year, which has been programmed to execute a young woman whose unborn son is the key to humanity's future salvation.", AssetsConst::TERMINATOR, "1984", "James Cameron", { "Arnold Schwarzenegger", "Linda Hamilton", "Michael Biehn" }, { "Action","Sci-Fi" }));
	movie_list.push_back(new Movie("Star Wars: Episode IV - A New Hope", "Luke Skywalker joins forces with a Jedi Knight, a cocky pilot, a Wookiee and two droids to save the galaxy from the Empire's world-destroying battle station, while also attempting to rescue Princess Leia from the mysterious Darth Vader.", AssetsConst::ANEWHOPE, "1997", "George Lucas", { "Mark Hamill", "Harrison Ford", "Carrie Fisher" }, { "Action","Adventure","Fantasy" }));
	movie_list.push_back(new Movie("Schindlers List", "In German-occupied Poland during World War II, industrialist Oskar Schindler gradually becomes concerned for his Jewish workforce after witnessing their persecution by the Nazis.", AssetsConst::SCHINDLERSLIST, "1994", "Steven Spielberg", { "Liam Neeson", "Ralph Fiennes", "Ben Kingsley" }, { "Drama","History" }));
	movie_list.push_back(new Movie("The Chronicles Of Narnia", "Four kids travel through a wardrobe to the land of Narnia and learn of their destiny to free it with the guidance of a mystical lion.", AssetsConst::NARNIA, "2005", "Andrew Adamson", { "Tilda Swinton","Geiorgie Henley","William Moseley" }, { "Adventure","Fantasy" }));
	movie_list.push_back(new Movie("Home Alone", "An eight-year-old troublemaker, mistakenly left home alone, must defend his home against a pair of burglars on Christmas eve.", AssetsConst::HOMEALONE, "1980", "Chris Columbus", { "Macaulay Culkin", "Joey Pesci", "Danel Stern" }, { "Comedy" , "Adventure" }));
	movie_list.push_back(new Movie("Pulp Fiction", "The lives of two mob hitmen, a boxer, a gangster and his wife, and a pair of diner bandits intertwine in four tales of violence and redemption.", AssetsConst::PULPFICTION, "1995", "Quentin Tarantino", { "John Travolta", "Uma Thurman", "Samuel L. Jackson" }, { "Crime", "Drama" }));
	movie_list.push_back(new Movie("MidSommar", "A couple travels to Northern Europe to visit a rural hometown's fabled Swedish mid-summer festival. What begins as an idyllic retreat quickly devolves into an increasingly violent and bizarre competition at the hands of a pagan cult.", AssetsConst::MIDSOMMAR, "2019", "Ari Ster", { "Florence Pugh","Jack Reynor","Vilhelm Blomgren" }, { "Horror","Drama" }));
	movie_list.push_back(new Movie("The Invisible Man", "A scientist finds a way of becoming invisible, but in doing so, he becomes murderously insane.", AssetsConst::THEINVISIBLEMAN, "1950", "James Whale", { "Claude Rains","Gloria Stuart","William Harrigan" }, { "Horror", "Sci-Fi" }));

	// Placing all movies in the right position

	size_t size = movie_list.size();
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j <= 4; j++)
		{

			movie_list[j + (i * 3 + i * 1 + i * 1)]->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - i * 6.3)));
			movie_list[j + (i * 3 + i * 1 + i * 1)]->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + j * 5.5);
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

//Destroying our objects
GUI::~GUI()
{
	for (const auto& movie : movie_list)
	{
		delete movie;
	}
	for (const auto& widget : widgets)
	{
		delete widget;
	}

	movie_list.clear();
	widgets.clear();
}

GUI* GUI::Get()
{
	if (!s_gui)
	{
		s_gui = new GUI();
	}
	return s_gui;
}

void GUI::releaseInstance()
{
	if (s_gui)
	{
		delete s_gui;
	}
	s_gui = nullptr;
}
