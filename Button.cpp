#include "Button.h"
#include "Mouse.h"
#include "Image.h"
#include "Drawer.h"
#include "Event.h"

Button::Button( Vector center_pos ) :
_state( STATE_NONE ),
_pos( center_pos ) {
}

Button::~Button( ) {
}

void Button::update( ) {
	switch ( _state ) {
	case STATE_CLICKED:
		_state = STATE_NONE;

	case STATE_NONE:
		updateDefault( );
		break;

	case STATE_PUSH:
		updatePush( );
		break;

	default:
		break;
	}
}

void Button::setDefaultImagePath( std::string path ) {
	_default_button_path = path;
	
	// ƒTƒCƒY‚ðŽæ“¾
	DrawerPtr drawer = Drawer::getTask( );
	ImagePtr image = drawer->getImage( path );

	_size = Vector( image->getImageWidth( ), image->getImageHeight( ) );
}

void Button::setClickedImagePath( std::string path ) {
	_clicked_button_path = path;
}

void Button::setEvent( EventPtr event ) {
	_event = event;
}

ImageConstPtr Button::getImage( ) const {
	DrawerPtr drawer = Drawer::getTask( );

	std::string path = ( _state != STATE_PUSH ? _default_button_path : _clicked_button_path );
	ImagePtr image = drawer->getImage( path );

	Vector half_size = _size;
	half_size *= 0.5;

	image->setPos( ( int )( _pos.x - half_size.x ), ( int )( _pos.y - half_size.y ) );
	return image;
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

	// event
	if ( _event != EventPtr( ) ) {
		_event->activate( );
	}
}

bool Button::onButton( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	Vector half_size = _size;
	half_size *= 0.5;
	
	if ( pos.x < _pos.x - half_size.x ||
		 pos.y < _pos.y - half_size.y ) {
		return false;
	}

	if ( pos.x > _pos.x + half_size.x ||
		 pos.y > _pos.y + half_size.y ) {
		return false;
	}

	return true;
}

bool Button::isClicked( ) const {
	return ( _state == STATE_CLICKED );
}
