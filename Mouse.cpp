#include "Mouse.h"
#include "DxLib.h"
#include "Manager.h"
#include <limits.h>

MousePtr Mouse::getTask( ) {
	return std::dynamic_pointer_cast< Mouse >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Mouse::Mouse( ) :
_click_left( 0 ),
_click_right( 0 ),
_clickup_left( false ),
_clickup_right( false ) {
}

Mouse::~Mouse( ) {
}

void Mouse::initialize( ) {
}

void Mouse::update( ) {
	int mouse_data = GetMouseInput( );
	updateClickingLeft( mouse_data );
	updateClickingRight( mouse_data );
}

void Mouse::updateClickingLeft( const int& mouse_data ) {
	int past = _click_left;

	if ( mouse_data & MOUSE_INPUT_LEFT ) {
		_click_left = ( _click_left + 1 ) % USHRT_MAX;
	} else {
		_click_left = 0;
	}

	// click up
	if ( past > 0 && _click_left == 0 ) {
		_clickup_left = true;
	} else {
		_clickup_left = false;
	}
}

void Mouse::updateClickingRight( const int& mouse_data ) {
	int past = _click_right;
	
	if ( mouse_data & MOUSE_INPUT_RIGHT ) {
		_click_right = ( _click_right + 1 ) % USHRT_MAX;
	} else {
		_click_right = 0;
	}

	// click up
	if ( past > 0 && _click_right == 0 ) {
		_clickup_right = true;
	} else {
		_clickup_right = false;
	}
}

Vector Mouse::getPoint( ) const {
	int x;
	int y;
	GetMousePoint( &x, &y );
	return Vector( x, y );
}

bool Mouse::isClickDownLeft( ) const {
	if ( _click_left == 1 ) {
		return true;
	}
	return false;
}

bool Mouse::isClickDownRight( ) const {
	if ( _click_right == 1 ) {
		return true;
	}
	return false;
}

bool Mouse::isClickUpLeft( ) const {
	return _clickup_left;
}

bool Mouse::isClickUpRight( ) const {
	return _clickup_right;
}

int Mouse::getClickingLeft( ) const {
	return _click_left;
}

int Mouse::getClickingRight( ) const {
	return _click_right;
}