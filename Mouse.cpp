#include "Mouse.h"
#include "DxLib.h"
#include "Manager.h"
#include <limits.h>

MousePtr Mouse::getTask( ) {
	return std::dynamic_pointer_cast< Mouse >( Manager::getInstance( )->getTask( getTag( ) ) );
}

std::string Mouse::getTag( ) {
	return "MOUSE_EVENT";
}

Mouse::Mouse( ) :
_mouse( NULL ),
_click_left( 0 ),
_click_right( 0 ),
_clickup_left( false ),
_clickup_right( false ) {
	initialize( );
}

Mouse::~Mouse( ) {
}

void Mouse::initialize( ) {
}

void Mouse::update( ) {
	_clickup_left = false;
	_clickup_right = false;
	_mouse = GetMouseInput( );
	calcLeftClick( );
	calcRightClick( );

	int x;
	int y;
	GetMousePoint( &x, &y );
	_pos = Vector( x, y );
}

void Mouse::calcLeftClick( ) {
	if ( _mouse & MOUSE_INPUT_LEFT ) {
		_click_left = ( _click_left + 1 ) % INT_MAX;
		return;
	}

	//ó£ÇµÇΩèuä‘Çåüím
	if ( _click_left != 0 ) {
		_clickup_left = true;
	}
	_click_left = 0;
}

void Mouse::calcRightClick( ) {
	if ( _mouse & MOUSE_INPUT_RIGHT ) {
		_click_right = ( _click_right + 1 ) % INT_MAX;
		return;
	}

	//ó£ÇµÇΩèuä‘Çåüím
	if ( _click_right != 0 ) {
		_clickup_right = true;
	}
	_click_right = 0;
}

Vector Mouse::getPoint( ) const {
	return _pos;
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