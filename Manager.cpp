#include "Manager.h"
#include "Base.h"
#include "DxLib.h"

Manager* Manager::_instance = nullptr;

const int DEFAULT_GRAPH_WIDTH   = 1920;
const int DEFAULT_GRAPH_HEIGHT  = 1080;
const int DEFAULT_GRAPH_DEPTH   = 32;
const int DEFAULT_SCREEN_WIDTH  = 1280;
const int DEFAULT_SCREEN_HEIGHT = 720;
const int DEFAULT_WINDOW_MODE   = 1;
const float DEFAULT_CAMERA_NEAR = 1.0f;
const float DEFAULT_CAMERA_FAR  = 50.0f;

Manager::Manager( ) :
_window_mode( TRUE ),
_window_width( DEFAULT_SCREEN_WIDTH ),
_window_height( DEFAULT_SCREEN_HEIGHT ),
_screen_width( DEFAULT_GRAPH_WIDTH ),
_screen_height( DEFAULT_GRAPH_HEIGHT ),
_draw_screen( DX_SCREEN_BACK ),
_camera_near( DEFAULT_CAMERA_NEAR ),
_camera_far( DEFAULT_CAMERA_FAR ) {
	ChangeWindowMode( TRUE );
	SetGraphMode( _screen_width, _screen_height, 32 );
	SetWindowSize( _window_width, _window_height );
	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );

	DxLib_Init( );
	initializeDxlib( );
}

Manager::~Manager( ) {
	DxLib_End( );
}

Manager* Manager::getInstance( ) {
	if ( !_instance ) {
		_instance = new Manager;
	}
	return _instance;
}

void Manager::finalize( ) {
	if ( _instance ) {
		delete _instance;
		_instance = nullptr;
	}
}

void Manager::initializeDxlib( ) {
	SetUseLighting( FALSE );
	SetLightEnable( FALSE );
	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );
	SetDrawScreen( _draw_screen );
	SetCameraNearFar( _camera_near, _camera_far );
	SetUseBackCulling( TRUE );
}

void Manager::startGame( ) {
	initializeTasks( );

	// main loop
	while ( !CheckHitKey( KEY_INPUT_ESCAPE ) ) {
		if ( ProcessMessage( ) != 0 ) {
			break;	
		}

		for ( std::pair< std::string, BasePtr > task : _tasks ) {
			task.second->update( );
		}
	}

	finalizeTasks( );
}

void Manager::initializeTasks( ) {
	for ( std::pair< std::string, BasePtr > task : _tasks ) {
		task.second->initialize( );
	}
}

void Manager::finalizeTasks( ) {
	for ( std::pair< std::string, BasePtr > task : _tasks ) {
		task.second->finalize( );
	}
}

void Manager::add( std::string tag, BasePtr ptr ) {
	_tasks[ tag ] = ptr;
}

BasePtr Manager::getTask( std::string tag ) {
	if ( _tasks.count( tag ) < 1 ) {
		return BasePtr( );
	}

	return _tasks[ tag ];
}

void Manager::changeWindowMode( bool flag ) {
	_window_mode = ( flag ? TRUE : FALSE );
	ChangeWindowMode( _window_mode );
	initializeDxlib( );
}

void Manager::setWindowSize( int width, int height ) {
	_window_width = width;
	_window_height = height;

	SetWindowSize( width, height );
}

void Manager::setScreenSize( int width, int height ) {
	_screen_width  = width;
	_screen_height = height;

	SetGraphMode( _screen_width, _screen_height, 32 );
	setWindowSize( _screen_width, _screen_height );
	initializeDxlib( );
}

void Manager::setCameraNearFar( float camera_near, float camera_far ) {
	_camera_near = camera_near;
	_camera_far = camera_far;
	initializeDxlib( );
}

int Manager::getWindowWidth ( ) const {
	return _window_width;
}

int Manager::getWindowHeight( ) const {
	return _window_height;
}

int Manager::getScreenWidth ( ) const {
	return _screen_width;
}

int Manager::getScreenHeight( ) const {
	return _screen_height;
}