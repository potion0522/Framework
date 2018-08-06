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
	void setCameraNearFar( float camera_near, float camera_far );

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
	float _camera_near;
	float _camera_far;
};

