#pragma once
#include "smart_ptr.h"
#include "Base.h"
#include <map>

PTR( Manager );
PTR( DxSetting );

class Manager {
public:
	Manager( );
	virtual ~Manager( );

public:
	static ManagerPtr getInstance( );
	static void initialize( );
	static void finalize( );

public:
	void update( );
	void allInitialize( );
	void add( std::string tag, BasePtr ptr );
	BasePtr getTask( std::string tag );
	bool isFin( ) const;

public:
	void setWindowSize( int width, int height );
	void setScreenSize( int width, int height );
	void changeWindowMode( bool flag );

public:
	int getWindowWidth ( ) const;
	int getWindowHeight( ) const;
	int getScreenWidth ( ) const;
	int getScreenHeight( ) const;

private:
	bool _fin;
	static ManagerPtr _instance;
	DxSettingPtr _setting;
	std::map< std::string, BasePtr > _exe;
};

