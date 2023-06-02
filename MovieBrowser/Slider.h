#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"


// Defines a Slider class, which is a widget that can be used to filter a list of movies by year.
// The Slider class has a clickable box that can be dragged to set the year based on the movement of the mouse of the user.
struct ClickableBox
{
private:

    // The x and y position of the box
    float m_positionX{};
    float m_positionY{};

    //Width and height of the clickable box
    static constexpr float m_box_width{ 0.2f };
    static constexpr float m_box_height{ 0.5f };

public:
    
    float getPosX() const { return m_positionX; }
    float getPosY() const { return m_positionY; }

    void setPosX(float x) { m_positionX = x; }
    void setPosY(float y) { m_positionY = y; }
 
    float getBoxWidth() const { return m_box_width; }
    float getBoxHeight() const { return m_box_height; }
};

namespace SliderPosition
{
    enum class Type
    {
        FROM,
        TO
    };
}

class Slider : public Widget
{
private:

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
    Checks if the given movie meets the requirements for filtering (checks if it is filtered by other widgets),
    used to sychronize all filters with all widgets that can filter, together.
    \param movie: a pointer to the movie
    \return true if the movie meets the requirements
    */
    bool hasRequirements(const Movie* movie) const;
    float getHeightOffset() const override { return m_height_offset; }

private:

    enum m_slider_state
    {
        SLIDER_IDLE,        // Slider is not being dragged.
        SLIDER_RELEASED,    // Slider was previously being draggedn and now is released
        SLIDER_DRAGGING     // Slider is now being dragged.
    };

    const SliderPosition::Type m_slider_position_type{};

    // The clickable box for the slider
    ClickableBox box;

    // The current state of the slider
    m_slider_state m_status_slider{ SLIDER_IDLE };

    // The text to display on the slider
    const std::string m_text{};

    // Defines the min/max value of the slider
    const int m_min_value{};
    const int m_max_value{};

    // The value that the slider is currently set to
    int m_value{};

    // A vector indicating all widgets this class needs to check, if they have filtered the movies previously.
    // This is used in order to sychronize all filters together. (Also watch MovieState.h + hasRequirements)
    std::vector<WidgetEnums::WidgetFilters> filterToBeChecked;

    static constexpr float SLIDER_BOX_X_OFFSET{ 3.5f };
    static constexpr float SLIDER_BOX_Y_OFFSET{ 0.05f };

    const float SLIDER_START_RANGE{ m_positionX + SLIDER_BOX_X_OFFSET };
    const float SLIDER_END_RANGE{ m_positionX - SLIDER_BOX_X_OFFSET };

    //This represents how much height will the slider need in order to appear when the dock comes down
    static constexpr float m_height_offset{ 4.0f };

public:

    //Constructs a new Slider
    //  \param float x: The x coordinate of the slider's position.
    //  \param float y: The y coordinate of the slider's position.
    //  \param const std::string_view text: It's the text to be displayed near the slider ("From","To")
    Slider(float posX, float posY, const std::string_view text,int min_v,int max_v, 
        SliderPosition::Type position, bool invisible = true);
    virtual ~Slider() = default;

};

#endif
