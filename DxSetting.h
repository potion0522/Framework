#pragma once
#include "smart_ptr.h"

PTR( DxSetting );

class DxSetting {
public:
	DxSetting( );
	virtual ~DxSetting( );

private:
	void initialize( );

public:
	void finalize( );

public:
	void changeWindowMode( bool flag );
	void setGraphMode( int width, int height );
	void setWindowSize( int width, int height );

public:
	void setCameraNearFar( float near_length, float far_length );
	void setUseLighting( bool flag );
	void setUseZBuffer( bool flag );

public:
	int getWindowWidth ( ) const;
	int getWindowHeight( ) const;
	int getScreenWidth ( ) const;
	int getScreenHeight( ) const;

private:
	int _window_mode;
	int _window_width;
	int _window_height;
	int _screen_width;
	int _screen_height;
	int _draw_screen;
};

