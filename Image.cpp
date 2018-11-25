#include "Image.h"
#include "DxLib.h"

Image::Image( ) :
_handle( -1 ),
_sx( 0 ),
_sy( 0 ),
_rate_x( 1 ),
_rate_y( 1 ),
_alpha( 255 ),
_draw_center( false ),
_image_width( 0 ) ,
_image_height( 0 ),
_angle( 0 ),
_flip( false ),
_rect( Rect( ) ),
_rgb( Bright( ) ) {
}

Image::~Image( ) {
	if ( _handle != -1 ) {
		DeleteGraph( _handle );
	}
}

void Image::draw( ) const {
	{ // �`��ݒ�

		// �����x
		if ( _alpha != 255 ) {
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, _alpha );
		}
		// RGB
		if ( _rgb.red != 255 || _rgb.green != 255 || _rgb.blue != 255 ) {
			SetDrawBright( _rgb.red, _rgb.green, _rgb.blue );
		}
	}



	{ // �`��
		switch ( selectDrawMode( ) ) {
			case DRAW_MODE_NORMAL: { // �ʏ�
				drawNormal( );
			} break;

			case DRAW_MODE_RECT: { // �؂���
				drawRect( );
			} break;
			
			case DRAW_MODE_RECT_EXTEND: { // �؂���&���R�ό`(�g��)
				drawRectExtend( );
			} break;
		}
	}


	{ // �`��ݒ胊�Z�b�g

		// �����x��߂�
		if ( _alpha != 255 ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
		// RGB��߂�
		if ( _rgb.red != 255 || _rgb.green != 255 || _rgb.blue != 255 ) {
			SetDrawBright( 255, 255, 255 );
		}
	}
}

Image::DRAW_MODE Image::selectDrawMode( ) const {
	DRAW_MODE mode = DRAW_MODE_NORMAL;

	// rect ���ݒ肳��Ă�����؂���
	if ( _rect.width > 0 && _rect.height > 0 ) {
		mode = DRAW_MODE_RECT;

		// ����Ɋg�嗦�܂ł���Ȃ� rect extend
		if ( _rate_x != 1 || _rate_y != 1 ) {
			mode = DRAW_MODE_RECT_EXTEND;
		}
	}

	return mode;
}


void Image::drawNormal( ) const {
	int sx = _sx;
	int sy = _sy;

	// ���W����
	int adjust_x = 0;
	int adjust_y = 0;
	if ( _draw_center ) {
		adjust_x = _image_width  / 2 * -1;
		adjust_y = _image_height / 2 * -1;

		// RotaGraph�͐^�񒆍��W���w�肷�邽�߉������Ȃ�
		if ( _angle != 0 ) {
			adjust_x = 0;
			adjust_y = 0;
		}
	} else if ( _angle != 0 ) {
		// RotaGraph�͐^�񒆍��W���w�肷�邽�ߑ����Z
		adjust_x = _image_width  / 2;
		adjust_y = _image_height / 2;
	}
	sx += adjust_x;
	sy += adjust_y;


	if ( _angle != 0 ) {
		// ��]�`��
		DrawRotaGraph( sx, sy, 1, _angle, _handle, TRUE, _flip );
	} else {
		// �ʏ�`��
		if ( _flip ) {
			DrawTurnGraph( sx, sy, _handle, TRUE );
		} else {
			DrawGraph( sx, sy, _handle, TRUE );
		}
	}
}

void Image::drawRect( ) const {
	int sx = _sx;
	int sy = _sy;

	// ���W����
	int adjust_x = 0;
	int adjust_y = 0;
	if ( _draw_center ) {
		adjust_x = _rect.width  / 2 * -1;
		adjust_y = _rect.height / 2 * -1;

		// RotaGraph�͐^�񒆍��W���w�肷�邽�߉������Ȃ�
		if ( _angle != 0 ) {
			adjust_x = 0;
			adjust_y = 0;
		}
	} else if ( _angle != 0 ) {
		// RotaGraph�͐^�񒆍��W���w�肷�邽�ߑ����Z
		adjust_x = _rect.width  / 2;
		adjust_y = _rect.height / 2;
	}
	sx += adjust_x;
	sy += adjust_y;

	if ( _angle != 0 ) {
		// ��]�`��
		DrawRectRotaGraph( sx, sy, _rect.x, _rect.y, _rect.width, _rect.height, 1, _angle, _handle, TRUE, _flip );
	} else {
		// �ʏ�`��
		DrawRectGraph( sx, sy, _rect.x, _rect.y, _rect.width, _rect.height, _handle, TRUE, _flip );
	}
}

void Image::drawRectExtend( ) const {
	int sx = _sx;
	int sy = _sy;

	// ���W����
	if ( !_draw_center ) {
		// �S�̂̑傫��*Rate �̔������炷
		int adjust_x = ( int )( _rect.width  * _rate_x * 0.5 );
		int adjust_y = ( int )( _rect.height * _rate_y * 0.5 );
		
		sx = _sx + adjust_x;
		sy = _sy + adjust_y;
	}

	// �`����W�A�؂���J�n���W�A�؂��蕝�A�摜��]���S�A�g�嗦�A��]���A�摜�E���߁E���]
	DrawRectRotaGraph3( 
		sx, sy,
		_rect.x, _rect.y, 
		_rect.width, _rect.height,
		_rect.width / 2, _rect.height / 2, 
		_rate_x, _rate_y, 
		_angle, 
		_handle, TRUE, _flip );
}

void Image::setPos( int x, int y ) {
	_sx = x;
	_sy = y;
}

void Image::setRect( int rect_x, int rect_y, int width, int height ) {
	_rect.x      = rect_x;
	_rect.y      = rect_y;
	_rect.width  = width ;
	_rect.height = height;
}

void Image::setExtendRate( double rate_x, double rate_y ) {
	_rate_x = rate_x;
	_rate_y = rate_y;
}

void Image::setRotate( double radian ) {
	_angle = radian;
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
	if ( _handle != -1 ) {
		DeleteGraph( _handle );
	}

	_handle = LoadGraph( path );

	// image size ���擾
	if ( _handle != -1 ) {
		GetGraphSize( _handle, &_image_width, &_image_height );
	}

	return ( _handle != -1 );
}

int Image::getImageWidth( ) const {
	return _image_width;
}

int Image::getImageHeight( ) const {
	return _image_height;
}