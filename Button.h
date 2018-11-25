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
	Button( );
	virtual ~Button( );

public:
	void update( );
	void draw( ) const;

public:
	void setDefaultImage( ImagePtr image );
	void setPushImage( ImagePtr image );
	void setSize( int width, int height );

public:
	ImagePtr getDefaultImage( );
	ImagePtr getPushImage( );

private:
	void updateDefault( );
	void updatePush( );
	void updateClicked( );

private:
	// mouseÇ™É{É^Éìè„Ç…Ç†ÇÈÇ©Ç«Ç§Ç©
	bool onButton( ) const;

public:
	bool isClicked( ) const;

private:
	STATE _state;
	Vector _pos;
	int _width;
	int _height;

	ImagePtr _default_image;
	ImagePtr _push_image;
};

