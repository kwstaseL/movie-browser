#include "GUI.h"
//DONE

void GUI::draw()	//Drawing of all our classes
{
	if (m_state == STATUS_LOADING)
	{
		drawLoadingScreen();
	}
	else if (m_state == STATUS_STARTED)
	{
		drawStartedScreen();
	}
	else if (m_state == STATUS_MOVIE_PRESSED)
	{
		drawPressedMovieScreen();
	}

}

void GUI::update()	//Updating of all our classes
{
	if (m_state == STATUS_LOADING)
	{
		updateLoadingScreen();
	}
	else if (m_state == STATUS_STARTED)
	{
		updateStartedScreen();
	}
	else if (m_state == STATUS_MOVIE_PRESSED)
	{
		updatePressedMovieScreen();
	}

}

//Updating Start Screen
void GUI::updateStartedScreen()
{
	//For every movie and for our dock, update its state
	for (auto& movie : movie_list)
	{
		if (movie && !movie->isDisabled())
		{
			movie->update();

			if (movie->isClickTriggered() && movie->isActive())
			{
				m_state = STATUS_MOVIE_PRESSED;
				clickedMovie = movie;
			}
		}
	}

	for (const auto& widget : widgets)
	{
		if (widget)
		{
			widget->update();

			//Checking if the last active widget was a clear "filter" widget, so we can reset the sliders position
			if (lastActiveWidget && lastActiveWidget->getID() == 11)
			{
				for (const auto& w : widgets)
				{
					if (w->getID() == 9 || w->getID() == 10)
					{
						Slider* const s = dynamic_cast<Slider*>(w);
						s->clearSlider();
					}
					if (w->getID() == 12)
					{
						TextField* const t = dynamic_cast<TextField*>(w);
						t->deleteText();
					}
				}
				lastActiveWidget = nullptr;
			}

			if (widget->actionTriggered() && !widget->isOperating())
			{
				lastActiveWidget = widget;
				widget->setOperating(true);
				widget->takeAction(movie_list);
			}
		}

	}

}

//Actual GUI drawing
void GUI::drawStartedScreen()
{
	//Background
	br.fill_opacity = 0.5f;
	br.outline_opacity = 0.0f;
	br.texture = AssetsConst::ASSET_PATH + static_cast<std::string>(AssetsConst::BACKGROUND);
	graphics::drawRect(CanvasConst::CANVAS_WIDTH / 2, CanvasConst::CANVAS_HEIGHT / 2, CanvasConst::CANVAS_WIDTH, CanvasConst::CANVAS_HEIGHT, br);

	for (const auto& movie : movie_list)
	{
		if (movie && !movie->isDisabled())
		{
			movie->draw();
		}
	}

	for (const auto& widget : widgets)
	{
		if (widget)
		{
			widget->draw();
		}

	}

}

void GUI::drawPressedMovieScreen()
{
	if (clickedMovie)
	{
		clickedMovie->drawInformation();
	}
}

void GUI::updatePressedMovieScreen()
{

	if (clickedMovie)
	{
		clickedMovie->setActive(false);
		clickedMovie->update();

		if (!clickedMovie->isClickTriggered())
		{
			m_state = STATUS_STARTED;
		}
	}

}

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

	movie_list.push_back(new Movie("Harry Potter and the Goblet Of Fire", "<Description>", AssetsConst::HARRY_POTTER, "2004", "Chris Columbus", { "Daniel Radcliffe","Rupert Grint","Richard Harris" }, { "Adventure", "Fantasy" }));
	movie_list.push_back(new Movie("The Godfather", "<Description>", AssetsConst::GODFATHER, "1972", "Francis Ford Coppola", { "Marlon Brando", "Al Pacino", "James Caan" }, { "Crime","Drama" }));
	movie_list.push_back(new Movie("Terminator", "<Description>", AssetsConst::TERMINATOR, "1984", "James Cameron", { "Arnold Schwarzenegger", "Linda Hamilton", "Michael Biehn" }, { "Action","Sci-Fi" }));
	movie_list.push_back(new Movie("Star Wars: Episode IV - A New Hope", "<Description>", AssetsConst::ANEWHOPE, "1997", "George Lucas", { "Mark Hamill", "Harrison Ford", "Carrie Fisher" }, { "Action","Adventure","Fantasy" }));
	movie_list.push_back(new Movie("Schindlers List", "<Description>", AssetsConst::SCHINDLERSLIST, "1994", "Steven Spielberg", { "Liam Neeson", "Ralph Fiennes", "Ben Kingsley" }, { "Drama","History" }));
	movie_list.push_back(new Movie("The Chronicles Of Narnia", "<Description>", AssetsConst::NARNIA, "2005", "Andrew Adamson", { "Tilda Swinton","Geiorgie Henley","William Moseley" }, { "Adventure","Fantasy" }));
	movie_list.push_back(new Movie("Home Alone", "<Description>", AssetsConst::HOMEALONE, "1980", "Chris Columbus", { "Macaulay Culkin", "Joey Pesci", "Danel Stern" }, { "Comedy" , "Adventure" }));
	movie_list.push_back(new Movie("Pulp Fiction", "<Description>", AssetsConst::PULPFICTION, "1995", "Quentin Tarantino", { "John Travolta", "Uma Thurman", "Samuel L. Jackson" }, { "Crime", "Drama" }));
	movie_list.push_back(new Movie("MidSommar", "A couple travels to Northern Europe to visit a rural hometown's fabled Swedish mid-summer festival. What begins as an idyllic retreat quickly devolves into an increasingly violent and bizarre competition at the hands of a pagan cult.", AssetsConst::MIDSOMMAR, "2019", "Ari Ster", { "Florence Pugh","Jack Reynor","Vilhelm Blomgren" }, { "Horror","Drama" }));
	movie_list.push_back(new Movie("The Invisible Man", "<Description>", AssetsConst::THEINVISIBLEMAN, "1950", "James Whale", { "Claude Rains","Gloria Stuart","William Harrigan" }, { "Horror", "Sci-Fi" }));

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

GUI* GUI::Get()		//Here we set it as static so we can use it without the need of an existing object, if there is no instance of gui made yet, make one and return it
					//So the next time get gets called, it won't make another instance and just return the existing one
{
	if (!s_gui)
	{
		s_gui = new GUI();
	}
	return s_gui;

}

void GUI::releaseInstance() //Delete object
{
	if (s_gui)
	{
		delete s_gui;
	}
	s_gui = nullptr;
}

//Drawing Loading Screen
void GUI::drawLoadingScreen()
{
}

//Updating Loading Screen
void GUI::updateLoadingScreen() const
{
}
