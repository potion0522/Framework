#pragma once
#include "smart_ptr.h"
#include <string>

PTR( Image );

class Image {
private:
	enum DRAW_MODE {
		DRAW_MODE_NORMAL,
		DRAW_MODE_ROTATE,
		DRAW_MODE_RECT,
		DRAW_MODE_EXTEND,
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
	void drawRotate( ) const;
	void drawRect( ) const;
	void drawExtend( ) const;
	void drawRectExtend( ) const;

public:
	void setHandle( int handle );
	// 描画座標: x,y　右下頂点(拡大時): x2,y2
	void setPos( int x, int y, int x2 = 0, int y2 = 0 );
	// 切り取り始めの頂点: recv_x,rect_y　横幅・縦幅: width,height
	void setRect( int rect_x, int rect_y, int width, int height );
	// ラジアンを指定
	void setAngle( double angle );
	void setBlendMode( unsigned char alpha = 255 );
	void setBright( unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255 );
	// setPos( x, y ) で指定した座標を中心にします(通常・切り取り描画のみ)
	void setCentral( bool center_draw );
	void setFlipX( bool flip );

public:
	bool load( std::string& path );
	int getImageWidth( ) const;
	int getImageHeight( ) const;
	int getHandle( ) const;

private:
	int _handle;
	int _width;
	int _height;
	double _angle;
	bool _draw_center;
	bool _flip;
	
	struct Screen {
		int x;
		int y;
		int x2;
		int y2;
	} _screen;

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

