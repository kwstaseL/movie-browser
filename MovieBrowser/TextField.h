#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Widget.h"
#include <stack>
#include <deque>

/*
    Represents a TextButton, which in our program has a text ("Search Movie"), and when pressed user can provide a title of a movie.
    The TextButton class is derived from the Widget class, which provides a common interface for interacting with different types of widgets.
    When filtering, we also take as consideration all the other widgets that may have filtered the movies.
*/
class TextField : public Widget
{
private:
    // Constants that store the height and width of the text field.
    const float m_Textfield_height{ 0.5f };
    const float m_Textfield_width{ 4.0f };

    // Variable that stores whether the user has typed in the text field.
    bool m_typed{ false };

    /*
     * Checks if the given movie meets the specified requirements for filtering.
     * @param movie The movie to check.
     * @return true if the movie has the filtered genre and is between the 2 years specified by the slider, false otherwise.
     */
    bool hasRequirements(const Movie* movie) const;

    // This variable acts like a "timer", when the timer surpasses a default value, we want to set m_typed to false, so user can type again
    int m_timer{ -1 };

    // We use a stack to keep in the out of sight words (that the user can't see) when the textfield gets overflowed with words
    // we keep the words that the user can't see in a stack.
    // When the user presses "BACKSPACE" we insert one-by-one each character in the front of the word
    std::stack<char> outofsight_words;

    // Deque that stores all the characters the user gave as input, we decided to use a deque because it
    // allows fast insertion and deletion at both its beginning and its end (O(1))
    std::deque<char> characters;

    // Contains a constant value to specify what text field it is ("Search Movie")
    const std::string m_text;

    // Keeps track of how many extra words are stored from the time the text field was "full"
    int extra_words = 0;

    // Keeps track if the text field is full or not
    bool isFull{ false };

    bool textInvisible{ false };

    /*
     * Searches for movies by title using the given list of movies.
     * @param movie_list The list of movies to search through.
     */
    void searchByTitle(const std::vector<Movie*>& movie_list);

    /*
     * Clears the state of the text field.
     */
    void clear() override;

    /*
     * Check if the mouse is inside the bounds of the text field (based on its height and width).
     * @param x The x coordinate of the mouse.
     * @param y The y coordinate of the mouse.
     * @return true if the mouse is inside the bounds of the text field, false otherwise.
     */
    bool contains(float x, float y) const;

    /*
     * Takes a list of movies and performs some actions on them.
     * @param movie_list The list of movies to perform actions on.
     */
    void takeAction(const std::vector<Movie*>& movie_list) override;

public:

    /*
     * Continuously draws the text field.
     */
    void draw() override;

    /*
     * Continuously updates the text field.
     */
    void update() override;

    /*
     * Constructs a new text field at the given position with the given text.
     * @param posX The x position of the text field.
     * @param posY The y position of the text field.
     * @param text The text to display in the text field.
     */
    TextField(float posX, float posY, const std::string_view text);
};

#endif