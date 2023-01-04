#ifndef WIDGET_H
#define WIDGET_H

#include "Movie.h"

/*

	<INSERT INFO ABOUT WIDGET>

*/

class Widget
{
private:

	static inline int s_idGenerator{};	//	ID Generator that inserts ID's when constructing a new Widget 

protected:

	//Variables that all widgets have and are using.

	//Represents the info we get from getMouseState 
	float mouse_X{};	
	float mouse_Y{};

	//Position X,Y
	float m_positionX{};
	float m_positionY{};

	bool m_highlighted{ false };	//Highlight

	bool operating{ false };	//Variable that tells if our widget is currently operating

	bool m_visible{ false };	//Variable that tells if our widget is invisible or not (a widget is invisible in our project if the dock is not yet down)

	bool m_action{ false };		//Represents the state in which its time for a widget to take action (filter based on genre/year or search a title..)

	static inline int s_focus{}; //Variable that tells who currently has the focus
	float m_height{ 0.0f };		//Height that every widget gains when dock is down.
	int m_uid{};			//ID of a widget


	//Functions that is used to request focus when doing an operation, and release focus when its done operating
	bool requestFocus();
	void releaseFocus();

	graphics::Brush brush;

public:

	void setActionTriggered(bool action) { m_action = action; }

	//Every virtual function is called polymorphically for every widget

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual bool isOperating() const { return operating; }
	virtual void setOperating(bool o) { operating = o; }

	//Returns if an action is Triggered
	virtual bool actionTriggered() const { return m_action; }

	/*
		Every widget has an action that it can operate on, for example filter by genre, filter by year..
		This function takes in a movie list which contains all movies with control variables for each one, and does a specific operation based on which class is called
	*/
	virtual void takeAction(const std::vector<Movie*>& movie_list) = 0;

	virtual int getID() const { return m_uid; }
	virtual void clear() = 0;

	virtual void setVisibility(bool v) { m_visible = v; }

	Widget(float posX, float posY);
	virtual ~Widget();
};



#endif





