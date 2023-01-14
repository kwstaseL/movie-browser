#pragma once
#include <unordered_map>


namespace WidgetEnums {

    //Enum represents if the widget filter is enabled or disabled. 
    enum class WidgetFilterState
    {
        ENABLED,
        DISABLED
    };

    //Enum that represents all the widget filters being used
    enum class WidgetFilters {

        GenreFilter,
        TitleFilter

    };

}

// Class where keep all the filtering states for each Movie and also some extra variables (eg isDisabled, isClickTriggered..).
// For Example when clicking "Action" Filter Button ,we want all the movies that have action genre in their genres, to appear,
// but if we also want to search for a movie , while action button is still on, we want to only show those movies that have "Action" as genre.
class MovieState
{
private:

    //We use a map here, so that is easy if we ever want to insert a new widget that also needs sychronizing, to just insert a new widgetFilterState in the map
    //This map represents different widget filters (GenreFilter,TitleFilter) and the correct output ENABLED,DISABLED depending if that filter it is ENABLED or DISABLED for a specific movie
    std::unordered_map<WidgetEnums::WidgetFilters, WidgetEnums::WidgetFilterState> widgetFilterStates;

    //This represents the state where a movie can't be highlighted/glown or information is can be drawen about it, but the image of the movie is still drawen.
    bool m_isUpdatable{ true };

    //Variable used to see if a movie is disabled, a movie is disabled (not updated or drawen) when it doesn't meet filters requirements.
    bool m_isDisabled{ false };

    //Used to store if a movie is clicked.
    bool m_clickTriggered{ false };

    //Used to store the last years that where filtered on the Slider.
    int lastFilterFromYear{ 1950 };
    int lastFilterToYear{ 2020 };

    //Stores all the current genres that are pressed by the user and the movie has
    int m_genreCount{ 0 };

public:

    //Updates the state of a widget filter
    void updateWidgetState(const WidgetEnums::WidgetFilters& WidgetKey, const WidgetEnums::WidgetFilterState& WidgetState)
    {
        widgetFilterStates[WidgetKey] = WidgetState;
    }

    //Gets the state of a widget
    const WidgetEnums::WidgetFilterState& getWidgetState(const WidgetEnums::WidgetFilters& WidgetKey) const
    {
        return widgetFilterStates.at(WidgetKey);
    }

    //Inserts a state of a new widget filter
    void insertNewWidgetState(const WidgetEnums::WidgetFilters& WidgetKey, const WidgetEnums::WidgetFilterState& WidgetState)
    {
        widgetFilterStates[WidgetKey] = WidgetState;
    }

    //Returns if this a movie can be highlighted/glown and information can drawen about it (if mouse if hovered on the movie).
    bool isUpdatable() const { return m_isUpdatable; }

    //Setters and Getters

    int getGenreCount() const { return m_genreCount; }
    void resetGenreCount() { m_genreCount = 0; }
    void AddGenreCount(int g) { m_genreCount += g; }

    void setDisabled(bool d) { m_isDisabled = d; }
    bool isDisabled() const { return m_isDisabled; }

    bool isClickTriggered() const { return m_clickTriggered; }
    void setClickTriggered(bool c) { m_clickTriggered = c; }

    void setUpdatable(bool a) { m_isUpdatable = a; }

    void setLastFilterFromYear(int y) { lastFilterFromYear = y; }
    int getLastFilterFromYear() const { return lastFilterFromYear; }

    void setLastFilterToYear(int y) { lastFilterToYear = y; }
    int getLastFilterToYear() const { return lastFilterToYear; }

};