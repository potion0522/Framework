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
	SetGraphMode( _screen_width, _screen_height, 32 );
	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );
	Set3DSoundOneMetre( 1.0f ); // 1.0で1m
	SetEnableXAudioFlag( TRUE );

	#ifdef FULLSCREEN
		ChangeWindowMode( FALSE );
		SetFullScreenResolutionMode( DX_FSRESOLUTIONMODE_NATIVE );
	#else
		ChangeWindowMode( TRUE );
	#endif

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
	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );
	SetDrawScreen( _draw_screen );

	SetUseBackCulling( FALSE );
	SetUseLighting( FALSE );
	SetLightEnable( FALSE );
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

void Manager::setUseBackCulling( bool flag ) {
	int flag_int = flag ? TRUE : FALSE;
	SetUseBackCulling( flag_int );
}

void Manager::setUseZBaffur( bool flag ) {
	int flag_int = flag ? TRUE : FALSE;
	SetUseZBuffer3D( flag_int );
}

void Manager::setWriteZBaffur( bool flag ) {
	int flag_int = flag ? TRUE : FALSE;
	SetWriteZBuffer3D( flag_int );
}

void Manager::setUseLighting( bool flag ) {
	int flag_int = flag ? TRUE : FALSE;
	SetUseLighting( flag_int );
}

void Manager::setUseLightTypeDir( bool flag, float dir_x, float dir_y, float dir_z ) {
	int flag_int = flag ? TRUE : FALSE;
	SetLightEnable( flag_int );
	if ( flag ) {
		ChangeLightTypeDir( VGet( dir_x, dir_y, dir_z ) );
	}
}

void Manager::setLightAmbient( float r, float g, float b ) {
	SetLightAmbColor( GetColorF( r, g, b, 1.0f ) );

	// 白にセットする
	MATERIALPARAM material;
	material.Diffuse  = GetColorF( 1.0f, 1.0f, 1.0f, 1.0f );
	material.Ambient  = GetColorF( 1.0f, 1.0f, 1.0f, 1.0f );
	material.Specular = GetColorF( 0.0f, 0.0f, 0.0f, 0.0f );
	material.Emissive = GetColorF( 0.0f, 0.0f, 0.0f, 0.0f );
	material.Power    = 0.0f; // スぺキュラの強さ
	SetMaterialParam( material );
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

int Manager::getNowCount( ) const {
	return GetNowCount( );
}