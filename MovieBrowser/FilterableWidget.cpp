#include "FilterableWidget.h"
/*
Checks if the given movie meets the requirements for filtering (checks if is already filtered or not by other widgets),
used to sychronize all filters with all widgets that can filter, together.
\param movie: a pointer to the movie to be checked
\return true if the movie meets the requirements else false
*/
FilterableWidget::FilterableWidget()
{
}

FilterableWidget::FilterableWidget(bool invisible)
{
	m_visible = !invisible;
}

bool FilterableWidget::hasRequirements(const Movie* const movie) const
{
    // Common implementation for all FilterableWidget subclasses except Slider
    // You can implement the common behavior here.

	if (movie)
	{
		for (const auto& filter : filterToBeChecked)
		{//If getWidgeState returns disabled, return false since this movie doesnt meet the requirementes for filtering
			if (movie->state_info.getWidgetState(filter) != WidgetEnums::WidgetFilterState::ENABLED)
			{
				return false;
			}
		}// Otherwise, if all the other widgets are enabled, check if it between the sliders years.
		return std::stoi(movie->getDate()) <= movie->state_info.getLastSelectedToYear() && std::stoi(movie->getDate()) >= movie->state_info.getLastSelectedFromYear();
	}

}