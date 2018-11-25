#pragma once
#include "smart_ptr.h"

PTR( Image );

/*
  �f�X�g���N�^�Ń�������������邽�߃n���h��������n���̂͋֎~
*/

class Image {
private:
	enum DRAW_MODE {
		DRAW_MODE_NORMAL,
		DRAW_MODE_RECT,
		DRAW_MODE_RECT_EXTEND
	};

public:
	Image( );
	virtual ~Image( );

public:
	void draw( ) const;

private:
	DRAW_MODE selectDrawMode( ) const;
	void drawNormal( ) const;
	void drawRect( ) const;
	void drawRectExtend( ) const;

public:
	// �`����W: x,y
	void setPos( int x, int y );
	// �g�嗦
	void setExtendRate( double rate_x, double rate_y );
	// �؂���n�߂̒��_: recv_x,rect_y�@�����E�c��: width,height
	void setRect( int rect_x, int rect_y, int width, int height );
	// ���W�A�����w��
	void setRotate( double radian );
	void setBlendMode( unsigned char alpha = 255 );
	void setBright( unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255 );
	// setPos( x, y ) �Ŏw�肵�����W�𒆐S�ɂ���(�ʏ�E�؂���`��̂�)
	void setCentral( bool center_draw );
	void setFlipX( bool flip );

public:
	bool load( const char* path );
	int getImageWidth( ) const;
	int getImageHeight( ) const;
	int getHandle( ) const;

private:
	int _handle;
	int _sx;
	int _sy;
	double _rate_x;
	double _rate_y;
	int _image_width;
	int _image_height;
	double _angle;
	bool _draw_center;
	bool _flip;

	struct Rect {
		int x;
		int y;
		int width;
		int height;
	} _rect;

	struct Bright {
		unsigned char red;
		unsigned char green;
		unsigned char blue;

		Bright( ) :
		red  ( 255 ),
		green( 255 ),
		blue ( 255 ) {
		}
	} _rgb;

	unsigned char _alpha;
};

