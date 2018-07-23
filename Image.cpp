#include "Image.h"
#include "DxLib.h"

Image::Image( ) :
_handle( -1 ),
_x( 0 ),
_y( 0 ),
_x2( 0 ),
_y2( 0 ),
_rect_sx( 0 ),
_rect_sy( 0 ),
_rect_width( 0 ),
_rect_height( 0 ) {
}

Image::~Image( ) {
}

void Image::draw( ) const {
	if ( _rect_width < 1 || _rect_height < 1 ) {
		DrawGraph( _x, _y, _handle, TRUE );
	} else if ( _x2 < 1 || _y2 < 1 ) {
		DrawRectGraph( _x, _y, _rect_sx, _rect_sy, _rect_width, _rect_height, _handle, TRUE, FALSE );
	} else {
		DrawRectExtendGraph( _x, _y, _x2, _y2, _rect_sx, _rect_sy, _rect_width, _rect_height, _handle, TRUE );
	}
}

void Image::setPos( int x, int y, int x2, int y2 ) {
	_x  = x;
	_y  = y;
	_x2 = x2;
	_y2 = y2;
}

void Image::setRect( int rect_x, int rect_y, int width, int height ) {
	_rect_sx     = rect_x;
	_rect_sy     = rect_y;
	_rect_width  = width ;
	_rect_height = height;
}

bool Image::load( std::string path ) {
	_handle = LoadGraph( path.c_str( ) );
	return ( _handle != -1 );
}