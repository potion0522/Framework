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
	void setPos( int x, int y, int x2 = 0, int y2 = 0 );
	void setRect( int rect_x, int rect_y, int width, int height );

public:
	bool load( std::string path );

private:
	int _handle;
	
	int _x;
	int _y;
	int _x2;
	int _y2;

	int _rect_sx;
	int _rect_sy;
	int _rect_width;
	int _rect_height;
};

