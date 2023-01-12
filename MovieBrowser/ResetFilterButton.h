#ifndef RESET_FILTER_BUTTON_H
#define RESET_FILTER_BUTTON_H

#include "Button.h"

/*
    Represents a ResetFilterButton, which in our program has a text ("Reset Filters"), and when pressed resets all movies to be enabled.
    The FilterGenreButton class is derived from the Button class, which provides a common interface for interacting with different types of Buttons.
    When resetting all the movies, we also clear each widget's states.
*/
class ResetFilterButton final : public Button
{
private:

    /*
     * Resets all movie control variables to their default values.
     *
     * \param movie_list A list of movies to apply the reset to.
     */
    void resetFilter(const std::vector<Movie*>& movie_list) const;

    /*
     * Called when the reset filter button is clicked.
     * Resets all applied filters.
     *
     * \param movie_list A list of movies to apply the reset to.
     */
    void takeAction(const std::vector<Movie*>& movie_list) override;

    void clear() override;
    
    //Continuously updates the reset filter button.
    void update() override;
    
    // Continuously draws the reset filter button.
    void draw() override;
 


public:


    /*
     * Constructs a new ResetFilterButton at the given position with the given text.
     * \param posX The x-coordinate of the button's position.
     * \param posY The y-coordinate of the button's position.
     * \param text The text to display on the button.
     */
    ResetFilterButton(float posX, float posY, const std::string_view text);
    virtual ~ResetFilterButton() = default;

};

#endif
