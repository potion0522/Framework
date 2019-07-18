#pragma once
#include "Task.h"
#include <map>

/*******************************************

ゲームのメインループや設定を行う

*******************************************/

class Manager {
private:
	Manager( );
	~Manager( );

public:
	static Manager* getInstance( );

public:
	void startGame( );
	void finalize( );
	void add( std::string tag, TaskPtr ptr );
	TaskPtr getTask( std::string tag );

private:
	void initializeDxlib( );
	void initializeTasks( );
	void finalizeTasks( );

public:
	void setWindowSize( int width, int height );
	void setScreenSize( int width, int height );
	void setUseBackCulling( bool flag );
	void setWriteZBaffur( bool flag );
	void setUseZBaffur( bool flag );
	void setUseLighting( bool flag );
	void setUseLightTypeDir( bool flag, float dir_x = 1.0f, float dir_y = -1.0f, float dir_z = 1.0f );
	void setLightAmbient( float r, float g, float b );

public:
	int getWindowWidth ( ) const;
	int getWindowHeight( ) const;
	int getScreenWidth ( ) const;
	int getScreenHeight( ) const;
	int getNowCount( ) const; // ミリ秒を返す

private:
	static Manager* _instance;
	std::map< std::string, TaskPtr > _tasks;
	
	int _window_mode;
	int _window_width;
	int _window_height;
	int _screen_width;
	int _screen_height;
	int _draw_screen;
	float _camera_near;
	float _camera_far;
};

