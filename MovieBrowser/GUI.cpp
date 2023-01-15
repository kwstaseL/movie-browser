#include "GUI.h"


// Draw is the function that is continuously running and drawing all our objects to the screen.
// - drawStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being drawned.	(STATUS_STARTED)
// - drawPressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.	(STATUS_MOVIE_PRESSED)

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

}

// Update is the function that is continuously running and updating all our objects to the screen.
// - updateStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being updated.	(STATUS_STARTED)
// - updatePressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.	(STATUS_MOVIE_PRESSED)
	
void GUI::update()
{

	if (m_state == STATUS_STARTED)
	{
		updateStartedScreen();
	}
	else if (m_state == STATUS_MOVIE_PRESSED)
	{
		updatePressedMovieScreen();
	}

}

// Updates the started screen (the screen with all movies and widgets are shown)

void GUI::updateStartedScreen()
{
	//Function which updates our starting screen

	//For every movie, update it.
	for (const auto& movie : movie_list)
	{
		if (movie)
		{
			movie->update();

			/*
				If a particular movie is clicked, and our movie is updatable (which means that this movie can be highlighted/glown and information can drawen about it (if mouse if hovered on the movie)..),
				change the state and start the scene where this movie's info is displayed
			*/
			if (movie->state_info.isClickTriggered() && movie->state_info.isUpdatable())
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

			//If for all widgets an action is triggered (a button is clicked, or text is typed in the textfield, or slider is being dragged..) and
			//The current widget which action is triggered is not operating currently, 
			//We run a function called takeAction which takes as data all movies, and does some filtering/cleaning (depending on which widget is called (button,textfield..))
			// or any particular other action needed upon the movies.

			if (widget->actionTriggered() && !widget->isOperating())
			{
				lastActiveWidget = widget;
				widget->setOperating(true);
				widget->takeAction(movie_list);
			}

			/*
			* Checking if the last active widget was a clear "filter" widget(id == 11), so we can call clear on all the other widgets polymorphically.
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

// Draws the started screen (the screen where all movies and widgets are shown)
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
		if (movie)
		{
			movie->draw();
		}
	}

	//For each widget we call its draw function
	for (const auto& widget : widgets)
	{
		if (widget)
		{
			widget->draw();
		}

	}

}

// Draws the pressed movie screen (where information about 1 movie is shown)
void GUI::drawPressedMovieScreen()
{
	//Drawing the scene when a movie is pressed
	if (clickedMovie)
	{
		clickedMovie->drawInformation();
	}
	else
	{
		return;
	}
}

// Updates the pressed movie screen (where information about 1 movie is shown)
void GUI::updatePressedMovieScreen()
{
	//Updating the scene when a movie is pressed

	if (clickedMovie)
	{
		clickedMovie->state_info.setUpdatable(false);//But we just set it to not updatable so information from the other scene about this movie doesn't show in this screen.
		clickedMovie->update();

		//If user released the mouse, go to the previous state
		if (!clickedMovie->state_info.isClickTriggered())
		{
			m_state = STATUS_STARTED;
			clickedMovie->state_info.setUpdatable(true);
		}
	}
	else
	{
		m_state = STATUS_STARTED;
		return;
	}

}

//Initializing all our objects (movies,widgets)
void GUI::init()
{
	graphics::preloadBitmaps(AssetsConst::ASSET_PATH);

	graphics::setFont("OpenSans-Regular.ttf");
	CreateMovies();
	CreateWidgets();

}

void GUI::CreateWidgets()
{
	//Creating all our widget objects

	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 8.3f, CanvasConst::CANVAS_HEIGHT / 1.28 - 12.0f - 2.0f, "Action"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 11.4f, CanvasConst::CANVAS_HEIGHT / 1.28 - 12.0f - 2.0f, "Drama"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 14.5f, CanvasConst::CANVAS_HEIGHT / 1.28 - 12.0f - 2.0f, "Horror"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 8.3f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Adventure"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 11.4f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Fantasy"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 14.5f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Sci-Fi"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 8.3f, CanvasConst::CANVAS_HEIGHT / 1.13 - 12.0f - 2.0f, "History"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 11.4f, CanvasConst::CANVAS_HEIGHT / 1.13 - 12.0f - 2.0f, "Animation"));
	widgets.push_back(new FilterGenreButton(CanvasConst::CANVAS_WIDTH / 15 + 14.5f, CanvasConst::CANVAS_HEIGHT / 1.13 - 12.0f - 2.0f, "Crime"));

	widgets.push_back(new Slider(CanvasConst::CANVAS_WIDTH / 15 + 11.5f, CanvasConst::CANVAS_HEIGHT / 1.20 - 12.0f - 2.0f, "From",1950,2020,SlilderFiltering::FilterBy::FilterByYear));

	widgets.push_back(new Slider(CanvasConst::CANVAS_WIDTH / 15 + 11.5f, CanvasConst::CANVAS_HEIGHT / 1.10 - 12.0f - 2.0f, "To",1950,2020,SlilderFiltering::FilterBy::FilterByYear));

	widgets.push_back(new ResetFilterButton(CanvasConst::CANVAS_WIDTH / 15 + 18.0f, CanvasConst::CANVAS_HEIGHT / 1.2 - 12.0f - 2.0f, "Clear Filter"));

	widgets.push_back(new TextField(CanvasConst::CANVAS_WIDTH / 15 + 17.6f, CanvasConst::CANVAS_HEIGHT / 1.15f - 12.0f - 2.0f, "Search Title/Dir/Prot",TextFieldFiltering::FilterBy::TITLE_PROTAGONIST_DIRECTOR));

	widgets.push_back(new Dock(CanvasConst::CANVAS_WIDTH / 2, -3.6f, widgets));	//For this program , we want all the widgets to appear on the dock,
	//thats why we are passing all of them to the dock (except for the dock itself).
}

void GUI::CreateMovies()
{
	//Creating all our movies, and placing each one in the right position

	movie_list.push_back(new Movie("Harry Potter and the Goblet Of Fire", "Harry Potter finds himself competing in a hazardous tournament between rival schools of magic, but he is distracted by recurring nightmares.", AssetsConst::HARRY_POTTER, "2004", "Chris Columbus", { "Daniel Radcliffe","Rupert Grint","Richard Harris" }, { "Adventure", "Fantasy" }));
	movie_list.push_back(new Movie("The Godfather", "The aging patriarch of an organized crime dynasty in postwar New York City transfers control of his clandestine empire to his reluctant youngest son.", AssetsConst::GODFATHER, "1972", "Francis Ford Coppola", { "Marlon Brando", "Al Pacino", "James Caan" }, { "Crime","Drama" }));
	movie_list.push_back(new Movie("Terminator", "A human soldier is sent from 2029 to 1984 to stop an almost indestructible cyborg killing machine, sent from the same year, which has been programmed to execute a young woman whose unborn son is the key to humanity's future salvation.", AssetsConst::TERMINATOR, "1984", "James Cameron", { "Arnold Schwarzenegger", "Linda Hamilton", "Michael Biehn" }, { "Action","Sci-Fi" }));
	movie_list.push_back(new Movie("Star Wars: Episode IV - A New Hope", "Luke Skywalker joins forces with a Jedi Knight, a cocky pilot, a Wookiee and two droids to save the galaxy from the Empire's world-destroying battle station, while also attempting to rescue Princess Leia from the mysterious Darth Vader.", AssetsConst::ANEWHOPE, "1997", "George Lucas", { "Mark Hamill", "Harrison Ford", "Carrie Fisher" }, { "Action","Adventure","Fantasy" }));
	movie_list.push_back(new Movie("Schindlers List", "In German-occupied Poland during World War II, industrialist Oskar Schindler gradually becomes concerned for his Jewish workforce after witnessing their persecution by the Nazis.", AssetsConst::SCHINDLERSLIST, "1994", "Steven Spielberg", { "Liam Neeson", "Ralph Fiennes", "Ben Kingsley" }, { "Drama","History" }));
	movie_list.push_back(new Movie("Spirited Away", "During her family's move to the suburbs, a sullen 10-year-old girl wanders into a world ruled by gods, witches, and spirits, and where humans are changed into beasts.", AssetsConst::SPIRITEDAWAY, "2001", "Hayao Miyazaki", { "Miyu Irino","Daveigh Chase","Suzanne Pleshette" }, { "Drama","Adventure","Fantasy","Animation"}));
	movie_list.push_back(new Movie("My Neighbor Totoro", "A heartwarming tale of childhood innocence, family love and the magic of nature as two sisters find solace and companionship in the forest spirit Totoro, during a difficult time of moving and their mother's illness.", AssetsConst::MYNEIGHBORTOTORO, "1988", "Hayao Miyazaki", { "Hitoshi Takagi", "Noriko Hidaka", "Chika Sakamoto" }, { "Animation" , "Adventure","Fantasy"}));
	movie_list.push_back(new Movie("Pulp Fiction", "The lives of two mob hitmen, a boxer, a gangster and his wife, and a pair of diner bandits intertwine in four tales of violence and redemption.", AssetsConst::PULPFICTION, "1995", "Quentin Tarantino", { "John Travolta", "Uma Thurman", "Samuel L. Jackson" }, { "Crime", "Drama" }));
	movie_list.push_back(new Movie("MidSommar", "A couple travels to Northern Europe to visit a rural hometown's fabled Swedish mid-summer festival. What begins as an idyllic retreat quickly devolves into an increasingly violent and bizarre competition at the hands of a pagan cult.", AssetsConst::MIDSOMMAR, "2019", "Ari Ster", { "Florence Pugh","Jack Reynor","Vilhelm Blomgren" }, { "Horror","Drama" }));
	movie_list.push_back(new Movie("Lord Of The Rings", "A meek Hobbit from the Shire and eight companions set out on a journey to destroy the powerful One Ring and save Middle-earth from the Dark Lord Sauron.", AssetsConst::LORDOFTHERINGS, "2001", "Peter Jackson", { "Elijah Wood","Ian McKellen","Orlando Bloom" }, { "History", "Fantasy","Adventure"}));

	size_t size = movie_list.size();

	for (size_t i{ 0 }; i < 2; i++)
	{
		for (size_t j{ 0 }; j <= 4; j++)
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

//This method returns the instance of the GUI class. If an instance does not already exist, it creates a new one.
GUI* GUI::Get()
{
	//Getting our GUI Instance

	if (!s_gui)
	{
		s_gui = new GUI();
	}
	return s_gui;
}

//This method destroys the instance of GUI.
void GUI::releaseInstance()
{
	//Destroying GUI Instance
	if (s_gui)
	{
		delete s_gui;
	}
	s_gui = nullptr;
}
