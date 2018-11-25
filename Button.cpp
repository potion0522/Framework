#include "Button.h"
#include "Mouse.h"
#include "Image.h"
#include "Drawer.h"
#include "Event.h"

Button::Button( ) :
_state( STATE_NONE ),
_pos( ),
_width( 0 ),
_height( 0 ) {
}

Button::~Button( ) {
}

void Button::update( ) {
	switch ( _state ) {
	case STATE_NONE:
		updateDefault( );
		break;

	case STATE_PUSH:
		updatePush( );
		break;

	case STATE_CLICKED:
		updateClicked( );
		break;

	default:
		break;
	}
}

void Button::updateDefault( ) {
	if ( !onButton( ) ) {
		return;
	}
	MousePtr mouse = Mouse::getTask( );
	if ( !mouse->isClickDownLeft( ) ) {
		return;
	}

	_state = STATE_PUSH;
}

void Button::updatePush( ) {
	if ( !onButton( ) ) {
		_state = STATE_NONE;
		return;
	}

	MousePtr mouse = Mouse::getTask( );
	if ( !mouse->isClickUpLeft( ) ) {
		return;
	}

	_state = STATE_CLICKED;
}

void Button::updateClicked( ) {
	_state = STATE_NONE;
}

void Button::draw( ) const {
	if ( _state == STATE_NONE ) {
		_default_image->draw( );
	} else {
		_push_image->draw( );
	}
}

void Button::setDefaultImage( ImagePtr image ) {
	_default_image = image;

	// サイズを取得
	setSize( _default_image->getImageWidth( ), _default_image->getImageHeight( ) );
}

void Button::setPushImage( ImagePtr image ) {
	_push_image = image;

	// サイズを取得
	setSize( _push_image->getImageWidth( ), _push_image->getImageHeight( ) );
}

void Button::setSize( int width, int height ) {
	_width  = width;
	_height = height;
}

ImagePtr Button::getDefaultImage( ) {
	return _default_image;
}

ImagePtr Button::getPushImage( ) {
	return _push_image;
}

bool Button::onButton( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	int half_width = _width / 2;
	int half_height = _height / 2;
	
	if ( pos.x < _pos.x - half_width ||
		 pos.y < _pos.y - half_height ) {
		return false;
	}

	if ( pos.x > _pos.x + half_width ||
		 pos.y > _pos.y + half_height ) {
		return false;
	}

	return true;
}

bool Button::isClicked( ) const {
	return ( _state == STATE_CLICKED );
}
