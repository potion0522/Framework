#include "Image.h"
#include "DxLib.h"

Image::Image( ) :
_handle( -1 ),
_alpha( 255 ),
_draw_center( false ){
	_screen = Screen( );
	_rect = Rect( );
	_rgb = Bright( );
}

Image::~Image( ) {
}

void Image::draw( ) const {
	if ( _alpha != 255 ) {
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, _alpha );
	}
	if ( _rgb.red != 255 || _rgb.green != 255 || _rgb.blue != 255 ) {
		SetDrawBright( _rgb.red, _rgb.green, _rgb.blue );
	}

	if ( _draw_center ) {
		DrawRotaGraph( _screen.x, _screen.y, 1, 0, _handle, TRUE );
	} else if ( _rect.width < 1 || _rect.height < 1 ) {
		DrawGraph( _screen.x, _screen.y, _handle, TRUE );
	} else if ( _screen.x2 < 1 || _screen.y2 < 1 ) {
		DrawRectGraph( _screen.x, _screen.y, _rect.x, _rect.y, _rect.width, _rect.height, _handle, TRUE, FALSE );
	} else {
		DrawRectExtendGraph( _screen.x, _screen.y, _screen.x2, _screen.y2, _rect.x, _rect.y, _rect.width, _rect.height, _handle, TRUE );
	}


	if ( _alpha != 255 ) {
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
	}
	if ( _rgb.red != 255 || _rgb.green != 255 || _rgb.blue != 255 ) {
		SetDrawBright( 255, 255, 255 );
	}
}

void Image::setPos( int x, int y, int x2, int y2 ) {
	_screen.x  = x;
	_screen.y  = y;
	_screen.x2 = x2;
	_screen.y2 = y2;
}

void Image::setRect( int rect_x, int rect_y, int width, int height ) {
	_rect.x      = rect_x;
	_rect.y      = rect_y;
	_rect.width  = width ;
	_rect.height = height;
}

void Image::setBlendMode( unsigned char alpha ) {
	_alpha = alpha;
}

void Image::setBright( unsigned char red, unsigned char green, unsigned char blue ) {
	_rgb.red   = red;
	_rgb.green = green;
	_rgb.blue  = blue;
}

void Image::setCentral( bool center_draw ) {
	_draw_center = center_draw;
}

bool Image::load( std::string path ) {
	_handle = LoadGraph( path.c_str( ) );
	return ( _handle != -1 );
}

int Image::getImageWidth( ) {
	GetGraphSize( _handle, &_width, &_height );
	return _width;
}

int Image::getImageHeight( ) {
	GetGraphSize( _handle, &_width, &_height );
	return _height;
}