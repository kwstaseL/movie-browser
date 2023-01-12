#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "Widget.h"

// This file defines a Slider class, which is a widget that can be used to filter a list of movies by year.
// The Slider class is derived from the Widget class, which provides a common interface.
// The Slider class has a clickable box that can be dragged to set the year based on the movement of the mouse of the user.

struct ClickableBox
{
private:

    // The x and y position of the box
    int m_positionX{};
    int m_positionY{};

    // Whether the box is currently active or not
    bool m_active{ false };

public:

    // Returns whether the box is active or not
    bool isActive() const { return m_active; }
    // Returns the x position of the box
    int getPosX() const { return m_positionX; }
    // Returns the y position of the box
    int getPosY() const { return m_positionY; }

    // Sets the x position of the box
    void setPosX(int x) { m_positionX = x; }
    // Sets the y position of the box
    void setPosY(int y) { m_positionY = y; }
    // Sets the active status of the box
    void setActive(bool a) { m_active = a; }
};

class Slider : public Widget
{
private:

    enum m_slider_state
    {
        SLIDER_IDLE,        // Slider is not being dragged.
        SLIDER_RELEASED,    // Slider was previously being draggedn and now is released
        SLIDER_DRAGGING     // Slider is now being dragged.
    };

    // The text to display on the slider
    const std::string m_text;

    // A vector indicating all widgets this class needs to check, if they have filtered the movies previously.
    // This is used in order to sychronize all filters together. (Also watch MovieState.h + hasRequirements)
    std::vector<WidgetEnums::WidgetFilters> filterToBeChecked;

    // The current state of the slider
    m_slider_state m_status_slider{ SLIDER_IDLE };

    // The clickable box for the slider
    ClickableBox box;

    // The year that the slider is currently set to
    int m_year{};

    // Continously Updates the state of the slider
    void update() override;

    // Continuously draws the slider on the canvas.
    void draw() override;

    //Checks if the mouse is within the coordinates of the boxes slider
    // \param mouse_x: the x coordinate of the mouse
    // \param mouse_y: the y coordinate of the mouse
    // \return true if the mouse is within the boxes slider coordinates
    bool contains(float x, float y) const;

    // Filters the given list of movies by the year on the slider (filters by calling filterByYear)
    // \param movie_list : A vector of movies to be filtered by their year
    void takeAction(const std::vector<Movie*>& movie_list) override;

    // Clears the slider (coordinates of the box and the year present on each box)
    void clear() override;

    // Filter the list of movies based on the year on the slider, 
    // and taking into consideration all the other filters that might be active for a specfic movie.
    void filterByYear(const std::vector<Movie*>& movie_list);

    /*
    Checks if the given movie meets the requirements for filtering (checks if is already filtered by other widgets),
    used to sychronize all filters with all widgets that can filter, together.
    \param movie: a pointer to the movie to be checked
    \return true if the movie meets the requirements, false otherwise
    */
    bool hasRequirements(const Movie* movie) const;

    // Whether the slider is currently disabled or not
    bool m_disabled{ false };

    float m_height_offset{ 4.0f };
    float getHeightOffset() const override { return m_height_offset; }


public:

    //Constructs a new Slider
    //  \param float x: The x coordinate of the slider's position.
    //  \param float y: The y coordinate of the slider's position.
    //  \param const std::string_view text: It's the text to be displayed near the slider ("From","To")
    Slider(float posX, float posY, const std::string_view text);
    virtual ~Slider() = default;

};

#endif
