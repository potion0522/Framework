#include "Button.h"
#include "Mouse.h"
#include "Image.h"
#include "Drawer.h"

Button::Button( const char* tag, std::function< void( const char* ) > callback ) :
TAG( tag ),
_state( STATE_NONE ),
_pos( ),
_mat_rot( ),
_width( 0 ),
_height( 0 ),
_callback( callback ) {
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
	MousePtr mouse = Mouse::getTask( );
	if ( !mouse->isClickDownLeft( ) ) {
		return;
	}

	if ( !onButton( ) ) {
		return;
	}

	_state = STATE_PUSH;
}

void Button::updatePush( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( !mouse->isClickUpLeft( ) ) {
		return;
	}

	if ( !onButton( ) ) {
		_state = STATE_NONE;
		return;
	}

	_state = STATE_CLICKED;
}

void Button::updateClicked( ) {
	_state = STATE_NONE;
	_callback( TAG );
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
	if ( _mat_rot ) {
		_mat_rot.reset( );
	}
	if ( radian != 0 ) {
		_mat_rot = std::shared_ptr< Matrix >( new Matrix( Matrix::makeTransformRotation( Vector( 0, 0, -1 ), radian ) ) );
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

	if ( _mat_rot ) {
		// 回転があった場合は外積で当たり判定を取る
		Vector points[ 4 ] = {
			 Vector( -half_width, -half_height ), // 左上
			 Vector( -half_width,  half_height ), // 左下
			 Vector(  half_width,  half_height ), // 右下
			 Vector(  half_width, -half_height ), // 右上
		};

		// 回転させて中点を足す
		for ( int i = 0; i < 4; i++ ) {
			points[ i ] = _mat_rot->multiply( points[ i ] ) + _pos;
		}

		// 外積
		for ( int i = 0; i < 4; i++ ) {
			int idx1 = i;
			int idx2 = ( i + 1 ) % 4;
			Vector a = points[ idx1 ];
			Vector b = points[ idx2 ];
			double cross = ( b - a ).cross( mouse_pos - b ).z;
			if ( cross > 0 ) {
				return false;
			}
		}

	} else {
		// 回転がない場合は単純な条件
		if ( mouse_pos.x < _pos.x - half_width ||
			 mouse_pos.y < _pos.y - half_height ) {
			return false;
		}

		if ( mouse_pos.x > _pos.x + half_width ||
			 mouse_pos.y > _pos.y + half_height ) {
			return false;
		}
	}

	return true;
}

void Button::drawCollider( ) const {
	int half_width = _width / 2;
	int half_height = _height / 2;

	Vector points[ 4 ] = {
		Vector( -half_width, -half_height ), // 左上
		Vector( -half_width,  half_height ), // 左下
		Vector(  half_width,  half_height ), // 右下
		Vector(  half_width, -half_height ), // 右上
	};

	if ( _mat_rot ) {
		for ( int i = 0; i < 4; i++ ) {
			points[ i ] = _mat_rot->multiply( points[ i ] );
		}
	}

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < 4; i++ ) {
		int idx1 = i;
		int idx2 = ( i + 1 ) % 4;
		Vector a = points[ idx1 ] + _pos;
		Vector b = points[ idx2 ] + _pos;
		drawer->drawLine( ( float )a.x, ( float )a.y, ( float )b.x, ( float )b.y, 0xff0000 );
	}
}