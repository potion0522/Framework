#include "Image.h"
#include "DxLib.h"

Image::Image( ) :
_handle( -1 ),
_alpha( 255 ),
_draw_center( false ),
_width( 0 ) ,
_height( 0 ),
_angle( 0 ),
_flip( false ),
_screen( Screen( ) ),
_rect( Rect( ) ),
_rgb( Bright( ) ) {
}

Image::~Image( ) {
	if ( _handle != -1 ) {
		DeleteGraph( _handle );
	}
}

void Image::draw( ) const {
	{ // 描画設定

		// 透明度
		if ( _alpha != 255 ) {
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, _alpha );
		}
		// RGB
		if ( _rgb.red != 255 || _rgb.green != 255 || _rgb.blue != 255 ) {
			SetDrawBright( _rgb.red, _rgb.green, _rgb.blue );
		}
	}



	{ // 描画
		switch ( selectDrawMode( ) ) {
			case DRAW_MODE_NORMAL: { // 通常
				drawNormal( );
			} break;

			case DRAW_MODE_ROTATE: { // 回転
				drawRotate( );
			} break;

			case DRAW_MODE_RECT: { // 切り取り
				drawRect( );
			} break;
			
			case DRAW_MODE_EXTEND: { // 自由変形(拡大)
				drawExtend( );
			} break;
			
			case DRAW_MODE_RECT_EXTEND: { // 切り取り&自由変形(拡大)
				drawRectExtend( );
			} break;
		}
	}


	{ // 描画設定リセット

		// 透明度を戻す
		if ( _alpha != 255 ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
		// RGBを戻す
		if ( _rgb.red != 255 || _rgb.green != 255 || _rgb.blue != 255 ) {
			SetDrawBright( 255, 255, 255 );
		}
	}
}

Image::DRAW_MODE Image::selectDrawMode( ) const {
	DRAW_MODE mode = DRAW_MODE( );

	// angle があれば回転描画
	if ( _angle != 0 ) {
		mode = DRAW_MODE_ROTATE;
	}

	// rect が設定されていたら切り取り
	if ( _rect.width > 0 && _rect.height > 0 ) {
		mode = DRAW_MODE_RECT;
	}

	// pos の第二変数が設定されていたら拡大
	if ( _screen.x < _screen.x2 && _screen.y < _screen.y2 ) {
		mode = DRAW_MODE_EXTEND;
	}

	// 拡大と切り取り、または回転なら
	if ( ( _screen.x < _screen.x2 && _screen.y < _screen.y2 ) &&
		 ( _rect.width > 0        && _rect.height > 0 )       ||
		 ( _angle != 0 ) ) {
		mode = DRAW_MODE_RECT_EXTEND;
	}

	return mode;
}


void Image::drawNormal( ) const {
	Screen draw_pos = _screen;

	// 座標調整
	if ( _draw_center ) {
		draw_pos.x -= _width / 2;
		draw_pos.y -= _height / 2;
	}

	// 反転処理
	if ( _flip ) {
		DrawTurnGraph( draw_pos.x, draw_pos.y, _handle, TRUE );
	} else {
		DrawGraph( draw_pos.x, draw_pos.y, _handle, TRUE );
	}
}

void Image::drawRotate( ) const {
	Screen draw_pos = _screen;
	DrawRotaGraph( draw_pos.x, draw_pos.y, 1, _angle, _handle, TRUE, _flip );
}

void Image::drawRect( ) const {
	Screen draw_pos = _screen;
	if ( _draw_center ) {
		draw_pos.x -= ( int )( _rect.width  / 2 );
		draw_pos.y -= ( int )( _rect.height / 2 );
	}
	DrawRectGraph( draw_pos.x, draw_pos.y, _rect.x, _rect.y, _rect.width, _rect.height, _handle, TRUE, _flip );
}

void Image::drawExtend( ) const {
	Screen draw_pos = _screen;

	if ( _flip ) {
		Screen tmp = draw_pos;
		draw_pos.x = draw_pos.x2;
		draw_pos.y = draw_pos.y2;
		draw_pos.x2 = tmp.x;
		draw_pos.y2 = tmp.y;
	}
	DrawExtendGraph( draw_pos.x, draw_pos.y, draw_pos.x2, draw_pos.y2, _handle, TRUE );
}

void Image::drawRectExtend( ) const {
	Screen draw_pos = _screen;

	// 切り取り
	Rect rect = _rect;
	if ( rect.width < 1 || rect.height < 1 ) {
		rect.width  = _width;
		rect.height = _height;
	}

	// 拡大率
	double rate_x = ( double )( draw_pos.x2 - draw_pos.x ) / rect.width;
	double rate_y = ( double )( draw_pos.y2 - draw_pos.y ) / rect.height;

	// 描画座標、切り取り、画像回転中心、拡大率、回転率、画像・透過・反転
	DrawRectRotaGraph3( 
		draw_pos.x, draw_pos.y,
		rect.x, rect.y, rect.width, rect.height,
		rect.width / 2, rect.height / 2, 
		rate_x, rate_y, 
		_angle, 
		_handle, TRUE, _flip );
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

void Image::setAngle( double angle ) {
	_angle = angle;
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

void Image::setFlipX( bool flip ) {
	_flip = flip;
}

int Image::getHandle( ) const {
	return _handle;
}

bool Image::load( const char* path ) {
	_handle = LoadGraph( path );

	// image size を取得
	if ( _handle != -1 ) {
		GetGraphSize( _handle, &_width, &_height );
	}

	return ( _handle != -1 );
}

int Image::getImageWidth( ) const {
	return _width;
}

int Image::getImageHeight( ) const {
	return _height;
}