#ifndef WIDGET_H
#define WIDGET_H

#include "Movie.h"
#include <unordered_set>

/**
 * A base class for graphical user interface elements.
 */
class Widget
{
private:

    // ID Generator that inserts IDs when constructing a new Widget 
    static inline int s_idGenerator{}; 

protected:

    // Variables that all widgets have and use.

    // Represents the info we get from getMouseState 
    float mouse_X{};
    float mouse_Y{};

    std::unordered_set<Movie*> m_filteredMovies{};

    // Position X,Y
    float m_positionX{};
    float m_positionY{};

    // Variable that tells if our widget is highlighted
    bool m_highlighted{ false };

    // Variable that tells if our widget is currently operating
    bool operating{ false }; 

    // Variable that tells if our widget is invisible or not (a widget is invisible in our project if the dock is not yet down)
    bool m_visible{ false };

    // Represents the state in which it's time for a widget to take action (filter based on genre/year or search a title..)
    bool m_action{ false };

    // Variable that tells which widget currently has the focus
    static inline int s_focus{};

    // Height that every widget gains when dock is down.
    // ID of a widget
    int m_uid{};     

    float m_height_offset{};

    /*
     * Requests focus when doing an operation.
     * @return true if the focus was successfully requested, false if another widget already has the focus.
     */
    bool requestFocus();

    /*
     * Releases focus when the operation is complete.
     */
    void releaseFocus();

    graphics::Brush brush;

public:

    /*
     * Sets the action triggered state for the widget.
     * @param action The new action triggered state for the widget.
     */
    void setActionTriggered(bool action) { m_action = action; }

    // Every virtual function is called polymorphically for every widget

    float m_height{ 0.0f };

     // Updates the state of the widget.
    virtual void update() = 0;

    
     //Draws the widget.
    virtual void draw() = 0;

    /*
     * Gets the operating state of the widget.
     * @return true if the widget is operating, false otherwise.
     */
    virtual bool isOperating() const { return operating; }

    /*
     * Sets the operating state of the widget.
     *
     * @param o The new operating state for the widget
     */
    virtual void setOperating(bool o) { operating = o; }

    /*
     * Gets the action triggered state of the widget.
     * @return true if an action has been triggered, false otherwise.
     */
    virtual bool actionTriggered() const { return m_action; }

    /*
     * Performs a specific operation based on the type of widget being called.
     * @param movie_list A list of all the movies where we are going to operte on.
     */
    virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

   
     // Gets the ID of the widget.  
    virtual int getID() const { return m_uid; }

    //Clears the state of the widget.
    virtual void clear() = 0;

    //Sets the visibility of the widget.
    virtual void setVisibility(bool v) { m_visible = v; }

    virtual float getHeightOffset() { return m_height_offset; }

    /**
     * Constructs a new widget at the given position.
     *
     * @param posX The x position of the widget.
     * @param posY The y position of the widget.
     */
    Widget(float posX, float posY);

   //Destructs the widget.
    virtual ~Widget();
};

#endif
