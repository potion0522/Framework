#include "DxSetting.h"
#include "DxLib.h"

const int DEFAULT_GRAPH_WIDTH   = 1920;
const int DEFAULT_GRAPH_HEIGHT  = 1080;
const int DEFAULT_GRAPH_DEPTH   = 32;
const int DEFAULT_SCREEN_WIDTH  = 1280;
const int DEFAULT_SCREEN_HEIGHT = 720;
const int DEFAULT_WINDOW_MODE   = 1;
const float DEFAULT_CAMERA_NEAR = 1.0f;
const float DEFAULT_CAMERA_FAR  = 50.0f;

DxSetting::DxSetting( ) :
_window_mode( TRUE ),
_window_width( DEFAULT_SCREEN_WIDTH ),
_window_height( DEFAULT_SCREEN_HEIGHT ),
_screen_width( DEFAULT_GRAPH_WIDTH ),
_screen_height( DEFAULT_GRAPH_HEIGHT ),
_draw_screen( DX_SCREEN_BACK ),
_camera_near( DEFAULT_CAMERA_NEAR ),
_camera_far( DEFAULT_CAMERA_FAR ) {
	ChangeWindowMode( DEFAULT_WINDOW_MODE );
	SetGraphMode( _screen_width, _screen_height, 32 );
	SetWindowSize( _window_width, _window_height );
	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );
	int result = DxLib_Init( );
	initialize( );
}

DxSetting::~DxSetting( ) {
}

void DxSetting::finalize( ) {
	DxLib_End( );
}

void DxSetting::initialize( ) {
	SetUseLighting( FALSE );
	SetLightEnable( FALSE );
	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );
	SetDrawScreen( _draw_screen );
	SetCameraNearFar( _camera_near, _camera_far );
}

void DxSetting::changeWindowMode( bool flag ) {
	_window_mode = ( flag ? TRUE : FALSE );
	ChangeWindowMode( _window_mode );
	initialize( );
}

void DxSetting::setGraphMode( int width, int height ) {
	_screen_width = width;
	_screen_height = height;

	SetGraphMode( _screen_width, _screen_height, DEFAULT_GRAPH_DEPTH );
	setWindowSize( _screen_width, _screen_height );
	initialize( );
}

void DxSetting::setWindowSize( int width, int height ) {
	_window_width = width;
	_window_height = height;

	SetWindowSize( width, height );
}

void DxSetting::setCameraNearFar( float camera_near, float camera_far ) {
	_camera_near = camera_near;
	_camera_far = camera_far;
	initialize( );
}

int DxSetting::getWindowWidth ( ) const {
	return _window_width;
}

int DxSetting::getWindowHeight( ) const {
	return _window_height;
}

int DxSetting::getScreenWidth ( ) const {
	return _screen_width;
}

int DxSetting::getScreenHeight( ) const {
	return _screen_height;
}