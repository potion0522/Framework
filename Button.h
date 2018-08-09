#pragma once
#include "Vector.h"
#include "smart_ptr.h"
#include <string>

PTR( Image );
PTR( Event );

class Button {
public:
	enum STATE {
		STATE_NONE,
		STATE_PUSH,
		STATE_CLICKED,
		STATE_MAX
	};

public:
	Button( Vector center_pos );
	virtual ~Button( );

public:
	void update( );

public:
	void setDefaultImagePath( std::string path );
	void setClickedImagePath( std::string path );
	void setEvent( EventPtr event );

public:
	ImageConstPtr getImage( ) const;

private:
	void updateDefault( );
	void updatePush( );

private:
	bool onButton( ) const;

public:
	bool isClicked( ) const;

private:
	STATE _state;
	Vector _pos;
	Vector _size;

	EventPtr _event;
	std::string _default_button_path;
	std::string _clicked_button_path;
};

