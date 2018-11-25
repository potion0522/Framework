#pragma once
#include "smart_ptr.h"

PTR( Image );

/*
  デストラクタでメモリを解放するためハンドルだけを渡すのは禁止
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
	// 描画座標: x,y
	void setPos( int x, int y );
	// 拡大率
	void setExtendRate( double rate_x, double rate_y );
	// 切り取り始めの頂点: recv_x,rect_y　横幅・縦幅: width,height
	void setRect( int rect_x, int rect_y, int width, int height );
	// ラジアンを指定
	void setRotate( double radian );
	void setBlendMode( unsigned char alpha = 255 );
	void setBright( unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255 );
	// setPos( x, y ) で指定した座標を中心にする(通常・切り取り描画のみ)
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

