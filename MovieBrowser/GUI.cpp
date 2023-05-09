#include "GUI.h"


// Draw is the function that is continuously running and drawing all our objects to the screen.
// - drawStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being drawned.	(STATUS_STARTED)
// - drawPressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.	(STATUS_MOVIE_PRESSED)

void GUI::draw()
{
	switch (m_state)
	{
	case STATUS_STARTED:

		drawStartedScreen();
		break;

	case STATUS_MOVIE_PRESSED:

		drawPressedMovieScreen();
		break;

	}
}

// Update is the function that is continuously running and updating all our objects to the screen.
// - updateStartedScreen() -> Indicates the scene where all the objects(movies,widgets) appear and are being updated.	(STATUS_STARTED)
// - updatePressedMovieScreen() -> Indicates the scene where a movie is pressed, and information is displayed for that movie.	(STATUS_MOVIE_PRESSED)
	
void GUI::update()
{
	switch (m_state)
	{
	case STATUS_STARTED:

		updateStartedScreen();
		break;

	case STATUS_MOVIE_PRESSED:

		updatePressedMovieScreen();
		break;

	}
}

// Updates the started screen (the screen with all movies and widgets are shown)

void GUI::updateStartedScreen()
{
	//Function which updates our starting screen

	//For every movie, update it.
	for (const auto& movie : movies)
	{
		if (movie)
		{
			movie->update();

			/*
				If a particular movie is clicked, and our movie is updatable (which means that this movie can be highlighted/glown and information can drawen about it (if mouse if hovered on the movie)..),
				change the state and start the scene where this movie's info is displayed
			*/
			if (movie->state_info.isClickTriggered() && movie->state_info.isInformationVisible())
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
				widget->setOperating(true);
				widget->takeAction(movies);
			}

		}

	}

}

// Draws the started screen (the screen where all movies and widgets are shown)
void GUI::drawStartedScreen()
{
	//Drawing our Background
	brush.fill_opacity = 0.5f;
	brush.outline_opacity = 0.0f;
	brush.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::BACKGROUND);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT, brush);

	//For each movie we call Movie's draw function
	for (const auto& movie : movies)
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
		clickedMovie->drawMovieInformation();
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
	{// Set it to False so information from the other scene about this movie doesn't show in this screen.
		clickedMovie->state_info.setInformationVisible(false);
		clickedMovie->update();

		//If user released the mouse, go to the previous state
		if (!clickedMovie->state_info.isClickTriggered())
		{
			m_state = STATUS_STARTED;
			clickedMovie->state_info.setInformationVisible(true);
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
	createMovies();
	createWidgets();
}

void GUI::createWidgets()
{
	//Creating all our widget objects
	const float y_offset = 12.0f + 2.0f;
	const float x_offset = CanvasConst::CANVAS_WIDTH / 15;
	const float row1_y = CanvasConst::CANVAS_HEIGHT / 1.28 - y_offset;
	const float row2_y = CanvasConst::CANVAS_HEIGHT / 1.2 - y_offset;
	const float row3_y = CanvasConst::CANVAS_HEIGHT / 1.13 - y_offset;

	widgets.emplace_back(new FilterGenreButton(x_offset + 8.3f, row1_y, "Action"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 11.4f, row1_y, "Drama"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 14.5f, row1_y, "Horror"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 8.3f, row2_y, "Adventure"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 11.4f, row2_y, "Fantasy"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 14.5f, row2_y, "Sci-Fi"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 8.3f, row3_y, "History"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 11.4f, row3_y, "Animation"));
	widgets.emplace_back(new FilterGenreButton(x_offset + 14.5f, row3_y, "Crime"));

	widgets.emplace_back(new Slider(x_offset + 11.5f, row2_y, "From", 1970, 2020, SliderPosition::Type::FROM));
	widgets.emplace_back(new Slider(x_offset + 11.5f, CanvasConst::CANVAS_HEIGHT / 1.10 - y_offset, "To", 1970, 2020, SliderPosition::Type::TO));

	widgets.emplace_back(new TextField(x_offset + 17.6f, CanvasConst::CANVAS_HEIGHT / 1.15f - y_offset, "Search Title/Dir/Prot", TextFieldFiltering::FilterBy::TITLE_PROTAGONIST_DIRECTOR));
	widgets.emplace_back(new ResetFilterButton(x_offset + 18.0f, row2_y, "Clear Filter", widgets));
	widgets.emplace_back(new Dock(CanvasConst::CANVAS_WIDTH / 2, -3.5f, widgets));
}

void GUI::createMovies()
{
	//Creating all our movies, and placing each one in the right position

	movies.push_back(new Movie("Harry Potter and the Goblet Of Fire", "Harry Potter finds himself competing in a hazardous tournament between rival schools of magic, but he is distracted by recurring nightmares.", AssetsConst::HARRY_POTTER, "2004", "Chris Columbus", { "Daniel Radcliffe","Rupert Grint","Richard Harris" }, { "Adventure", "Fantasy" }));
	movies.push_back(new Movie("The Godfather", "The aging patriarch of an organized crime dynasty in postwar New York City transfers control of his clandestine empire to his reluctant youngest son.", AssetsConst::GODFATHER, "1972", "Francis Ford Coppola", { "Marlon brushando", "Al Pacino", "James Caan" }, { "Crime","Drama" }));
	movies.push_back(new Movie("Terminator", "A human soldier is sent from 2029 to 1984 to stop an almost indestructible cyborg killing machine, sent from the same year, which has been programmed to execute a young woman whose unborn son is the key to humanity's future salvation.", AssetsConst::TERMINATOR, "1984", "James Cameron", { "Arnold Schwarzenegger", "Linda Hamilton", "Michael Biehn" }, { "Action","Sci-Fi" }));
	movies.push_back(new Movie("Star Wars: Episode IV - A New Hope", "Luke Skywalker joins forces with a Jedi Knight, a cocky pilot, a Wookiee and two droids to save the galaxy from the Empire's world-destroying battle station, while also attempting to rescue Princess Leia from the mysterious Darth Vader.", AssetsConst::ANEWHOPE, "1997", "George Lucas", { "Mark Hamill", "Harrison Ford", "Carrie Fisher" }, { "Action","Adventure","Fantasy" }));
	movies.push_back(new Movie("Schindlers List", "In German-occupied Poland during World War II, industrialist Oskar Schindler gradually becomes concerned for his Jewish workforce after witnessing their persecution by the Nazis.", AssetsConst::SCHINDLERSLIST, "1994", "Steven Spielberg", { "Liam Neeson", "Ralph Fiennes", "Ben Kingsley" }, { "Drama","History" }));
	movies.push_back(new Movie("Spirited Away", "During her family's move to the suburbs, a sullen 10-year-old girl wanders into a world ruled by gods, witches, and spirits, and where humans are changed into beasts.", AssetsConst::SPIRITEDAWAY, "2001", "Hayao Miyazaki", { "Miyu Irino","Daveigh Chase","Suzanne Pleshette" }, { "Drama","Adventure","Fantasy","Animation"}));
	movies.push_back(new Movie("My Neighbor Totoro", "A heartwarming tale of childhood innocence, family love and the magic of nature as two sisters find solace and companionship in the forest spirit Totoro, during a difficult time of moving and their mother's illness.", AssetsConst::MYNEIGHBORTOTORO, "1988", "Hayao Miyazaki", { "Hitoshi Takagi", "Noriko Hidaka", "Chika Sakamoto" }, { "Animation" , "Adventure","Fantasy"}));
	movies.push_back(new Movie("Pulp Fiction", "The lives of two mob hitmen, a boxer, a gangster and his wife, and a pair of diner bandits intertwine in four tales of violence and redemption.", AssetsConst::PULPFICTION, "1995", "Quentin Tarantino", { "John Travolta", "Uma Thurman", "Samuel L. Jackson" }, { "Crime", "Drama" }));
	movies.push_back(new Movie("MidSommar", "A couple travels to Northern Europe to visit a rural hometown's fabled Swedish mid-summer festival. What begins as an idyllic retreat quickly devolves into an increasingly violent and bizarre competition at the hands of a pagan cult.", AssetsConst::MIDSOMMAR, "2019", "Ari Ster", { "Florence Pugh","Jack Reynor","Vilhelm Blomgren" }, { "Horror","Drama" }));
	movies.push_back(new Movie("Lord Of The Rings", "A meek Hobbit from the Shire and eight companions set out on a journey to destroy the powerful One Ring and save Middle-earth from the Dark Lord Sauron.", AssetsConst::LORDOFTHERINGS, "2001", "Peter Jackson", { "Elijah Wood","Ian McKellen","Orlando Bloom" }, { "History", "Fantasy","Adventure"}));

	const size_t movies_size = movies.size();

	const size_t numRows = 2;
	const size_t moviesPerRow = 5;

	const double posYFactor = 6.3;
	const double posXFactor = 5.5;

	size_t size = movies.size();

	for (size_t i = 0; i < numRows; i++) 
	{
		for (size_t j = 0; j < moviesPerRow; j++) 
		{
			size_t index = j + (i * moviesPerRow);

			if (index >= size) 
			{
				break;
			}

			Movie* movie = movies[index];
			movie->setPosY(CanvasConst::CANVAS_WIDTH / (abs(10 - 0.12 - i * posYFactor)));
			movie->setPosX(CanvasConst::CANVAS_HEIGHT / 5.75 + j * posXFactor);
		}
	}


}

//Destroying our objects
GUI::~GUI()
{

	for (const auto& movie : movies)
	{
		delete movie;
	}
	for (const auto& widget : widgets)
	{
		delete widget;
	}

	movies.clear();
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
