#pragma once
#include "Base.h"
#include <map>

class Manager {
private:
	Manager( );
	~Manager( );

public:
	static Manager* getInstance( );

public:
	void startGame( );
	void finalize( );
	void add( std::string tag, BasePtr ptr );
	BasePtr getTask( std::string tag );

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

public:
	int getWindowWidth ( ) const;
	int getWindowHeight( ) const;
	int getScreenWidth ( ) const;
	int getScreenHeight( ) const;
	int getNowCount( ) const; // ƒ~ƒŠ•b‚ð•Ô‚·

private:
	static Manager* _instance;
	std::map< std::string, BasePtr > _tasks;
	
	int _window_mode;
	int _window_width;
	int _window_height;
	int _screen_width;
	int _screen_height;
	int _draw_screen;
	float _camera_near;
	float _camera_far;
};

