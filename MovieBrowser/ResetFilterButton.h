#ifndef RESET_FILTER_BUTTON_H
#define RESET_FILTER_BUTTON_H

#include "Button.h"

/*
   Represents a ResetFilterButton, which in our program has a text ("Reset Filters"), and when pressed resets all movies to be enabled.
    When resetting all the movies by this button, all of the other widgets clear() function will be called polymorphically to clear their own states.
*/
class ResetFilterButton final : public Button
{
private:

    const std::vector<Widget*> m_widgets{};

private:

    /*
     * Resets all movie filter widgets to their default values and enables all movies.
     * When this function gets called, each widget will "clear" all their states automatically.
     * 
     * \param movie_list A list of our movies
     */
    void restoreMovieStates(const std::vector<Movie*>& movie_list) const;

    void clearWidgets();
    /*
    *  Called when the reset filter button is clicked.
    *  Resets all applied filters and all other widgets clear their own state.
    *
    * \param movie_list A list of our movies.
    */
    void takeAction(const std::vector<Movie*>& movie_list) override;

    void clear() override;
    
    //Continuously updates the reset filter button.
    void update() override;
    
    // Continuously draws the reset filter button.
    void draw() override;

public:

      /*
     * Constructs a new ResetFilterButton.
     * \param posX The x coordinate of the button's position.
     * \param posY The y coordinate of the button's position.
     * \param text The text to display on the button.
     */
    ResetFilterButton(float posX, float posY, const std::string_view text,const std::vector<Widget*>& widgets);
    virtual ~ResetFilterButton() = default;

};

#endif
