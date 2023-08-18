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

    void update() override;

    void draw() override;
    /*
    *  Called when the reset filter button is clicked.
    *  Resets all applied filters and all other widgets clear their own state.
    *
    * \param movie_list A list of our movies.
    */
    void takeAction(const std::vector<Movie*>& movie_list) override;
    /*
     * Resets all movie filter widgets to their default values and enables all movies.
     * When this function gets called, each widget will "clear" all their states automatically.
     *
     * \param movie_list A list of our movies
     */
    void restoreMovieStates(const std::vector<Movie*>& movie_list) const;

    // Called to clear all widgets when click the reset filter button
    void clearWidgets();

    void clear() override;

private:

    // Vector which keeps all the widgets to be resetted
    const std::vector<Widget*> m_widgets{};

public:

      /*
     * Constructs a new ResetFilterButton.
     * \param posX The x coordinate of the button's position.
     * \param posY The y coordinate of the button's position.
     * \param text The text to display on the button.
     */
    ResetFilterButton(float posX, float posY, const std::string_view text,const std::vector<Widget*>& widgets, bool invisible = true);
    virtual ~ResetFilterButton() = default;

};

#endif
