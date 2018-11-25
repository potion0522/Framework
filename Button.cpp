#include "Button.h"
#include "Mouse.h"
#include "Image.h"
#include "Drawer.h"
#include "Event.h"

Button::Button( ) :
_state( STATE_NONE ),
_pos( ),
_mat_rot( ),
_rotate( false ),
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

void Button::setPos( const Vector& pos ) {
	_pos = pos;
	_default_image->setPos( ( int )pos.x, ( int )pos.y );
	_push_image   ->setPos( ( int )pos.x, ( int )pos.y );
}

void Button::setRotate( double radian ) {
	if ( radian == 0 ) {
		_rotate = false;
	} else {
		_rotate = true;
		_mat_rot = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), radian );
	}
	_default_image->setRotate( radian );
	_push_image   ->setRotate( radian );
}

void Button::setDefaultImage( const char* path ) {
	DrawerPtr drawer = Drawer::getTask( );
	_default_image = drawer->getImage( path );
	_default_image->setCentral( true );

	// サイズを取得
	setCollisionSize( _default_image->getImageWidth( ), _default_image->getImageHeight( ) );
}

void Button::setPushImage( const char* path ) {
	DrawerPtr drawer = Drawer::getTask( );
	_push_image = drawer->getImage( path );
	_push_image->setCentral( true );

	// サイズを取得
	setCollisionSize( _push_image->getImageWidth( ), _push_image->getImageHeight( ) );
}

void Button::setCollisionSize( int width, int height ) {
	_width  = width;
	_height = height;
}

void Button::setAlpha( unsigned char alpha ) {
	_default_image->setBlendMode( alpha );
	_push_image->setBlendMode( alpha );
}

bool Button::onButton( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_pos = mouse->getPoint( );
	int half_width = _width / 2;
	int half_height = _height / 2;

	Vector left_up    = Vector( _pos.x - half_width, _pos.y - half_height );
	Vector right_down = Vector( _pos.x + half_width, _pos.y + half_height );

	// いったん保留
	//if ( _rotate ) {
	//	left_up = _mat_rot.multiply( left_up );
	//	right_down = _mat_rot.multiply( right_down );
	//}
	
	if ( mouse_pos.x < left_up.x ||
		 mouse_pos.y < left_up.y ) {
		return false;
	}

	if ( mouse_pos.x > right_down.x ||
		 mouse_pos.y > right_down.y ) {
		return false;
	}

	return true;
}

bool Button::isClicked( ) const {
	return ( _state == STATE_CLICKED );
}
