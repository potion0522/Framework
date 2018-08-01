#pragma once
#include "smart_ptr.h"
#include <string>

PTR( Image );

class Image {
public:
	Image( );
	virtual ~Image( );

public:
	void draw( ) const;

public:
	void setHandle( int handle );
	void setPos( int x, int y, int x2 = 0, int y2 = 0 );
	void setRect( int rect_x, int rect_y, int width, int height );
	void setBlendMode( unsigned char alpha = 255 );
	void setBright( unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255 );
	void setCentral( bool center_draw );

public:
	int getHandle( ) const;
	bool load( std::string path );

private:
	int _handle;
	bool _draw_center;
	
	struct Screen {
		int x;
		int y;
		int x2;
		int y2;
	} _screen;

	struct Rect {
		int x;
		int y;
		int width;
		int height;
	} _rect;

	struct Bright {
		unsigned char red;
		unsigned char green;
		unsigned char blue;

		Bright( ) :
		red  ( 255 ),
		green( 255 ),
		blue ( 255 ) {
		}
	} _rgb;

	unsigned char _alpha;
};

