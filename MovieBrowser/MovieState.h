#ifndef MOVIE_STATE_H
#define MOVIE_STATE_H

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
public:

    //Updates the state of a widget filter
    void updateWidgetState(const WidgetEnums::WidgetFilters& WidgetKey, const WidgetEnums::WidgetFilterState& WidgetState)
    {
        widgetFilterStates[WidgetKey] = WidgetState;
    }

    // Gets the state of a widget filter
    const WidgetEnums::WidgetFilterState& getWidgetState(const WidgetEnums::WidgetFilters& widgetKey) const {

        auto it = widgetFilterStates.find(widgetKey);
        if (it != widgetFilterStates.end()) {
            return it->second;
        }
        const WidgetEnums::WidgetFilterState defaultState = WidgetEnums::WidgetFilterState::DISABLED;
        return defaultState;

    }

    //Inserts a state of a new widget filter
    void insertNewWidgetState(const WidgetEnums::WidgetFilters& WidgetKey, const WidgetEnums::WidgetFilterState& WidgetState)
    {
        widgetFilterStates[WidgetKey] = WidgetState;
    }

    void resetMovieState()
    {
        for (auto& [key, value] : widgetFilterStates) {
            value = WidgetEnums::WidgetFilterState::ENABLED;
        }
        setDisabled(false);
        setLastSelectedFromYear(1970);
        setLastSelectedToYear(2020);
    }

    //Returns if this a movie can be highlighted/glown and information can drawen about it (if mouse if hovered on the movie).
    bool isInformationVisible() const { return _isInformationVisible; }

private:

    //We use a map here, so that is easy if we ever want to insert a new widget that also needs sychronizing, to just insert a new widgetFilterState in the map
    //This map represents different widget filters (GenreFilter,TitleFilter) and the correct output ENABLED,DISABLED depending if that filter it is ENABLED or DISABLED for a specific movie
    std::unordered_map<WidgetEnums::WidgetFilters, WidgetEnums::WidgetFilterState> widgetFilterStates;

    //This represents the state where a movie can't be highlighted/glown or information is can be drawen about it, but the image of the movie is still drawen.
    bool _isInformationVisible{ true };

    //Variable used to see if a movie is disabled, a movie is disabled (not updated or drawen) when it doesn't meet filters requirements.
    bool _isDisabled{ false };

    //Used to store if a movie is clicked.
    bool _clickTriggered{ false };

    // Represents the most recent year selected by the user for the "From" slider.
    int _lastSelectedFromYear{ 1970 };

    // Represents the most recent year selected by the user for the "To" slider.
    int _lastSelectedToYear{ 2020 };

    //Stores all the current genres that are pressed by the user and the movie has
    int _genreCount{ 0 };

public:

    //Setters and Getters

    int getGenreCount() const { return _genreCount; }
    void resetGenreCount() { _genreCount = 0; }
    void addGenreCount(int g) { _genreCount += g; }

    void setDisabled(bool d) { _isDisabled = d; }
    bool isDisabled() const { return _isDisabled; }

    bool isClickTriggered() const { return _clickTriggered; }
    void setClickTriggered(bool c) { _clickTriggered = c; }

    void setInformationVisible(bool a) { _isInformationVisible = a; }

    void setLastSelectedFromYear(int y) { _lastSelectedFromYear = y; }
    int getLastSelectedFromYear() const { return _lastSelectedFromYear; }

    void setLastSelectedToYear(int y) { _lastSelectedToYear = y; }
    int getLastSelectedToYear() const { return _lastSelectedToYear; }


};

#endif