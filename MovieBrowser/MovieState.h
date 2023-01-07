#pragma once

#include <unordered_map>

namespace WidgetEnums {

    enum class WidgetFilterState
    {
        ENABLED,
        DISABLED
    };

    enum class WidgetKeys {

        GenreFilter,
        TitleFilter
    };

}

class MovieState
{
private:


    //We use a map here, so that is easy if we ever want to insert a new widget, to insert a new widgetFilterState
    //This map represents different strings (hasFilteredGenre,hasFilteredText..) and the correct output ENABLED,DISABLED
    std::unordered_map<WidgetEnums::WidgetKeys, WidgetEnums::WidgetFilterState> widgetFilterStates;

    //This represents the state where a movie can't be highlighted/glown or information is drawen about it.
    bool m_isUpdatable{ true };

    //Variable used to see if a movie is disabled, a movie is disabled (not updated or drawen) when it doesn't meet filters requirements.
    bool m_isDisabled{ false };

    //Used to store if a movie is clicked.
    bool m_clickTriggered{ false };

    int lastFilterFromYear{ 1950 };
    int lastFilterToYear{ 2020 };

    int m_genreCount{ 0 };

public:

    // Update the state of a widget
    void updateWidgetState(const WidgetEnums::WidgetKeys& key, const WidgetEnums::WidgetFilterState& state)
    {
        widgetFilterStates[key] = state;
    }

    // Retrieve the state of a widget
    const WidgetEnums::WidgetFilterState& getWidgetState(const WidgetEnums::WidgetKeys& key) const
    {
        return widgetFilterStates.at(key);
    }

    void insertNewWidgetState(const WidgetEnums::WidgetKeys& key, const WidgetEnums::WidgetFilterState& state)
    {
        widgetFilterStates[key] = state;
    }

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


    //Returns if this a movie can be highlighted/glown or information can drawen about it (if mouse if hovered on them).
    bool isUpdatable() const { return m_isUpdatable; }

};