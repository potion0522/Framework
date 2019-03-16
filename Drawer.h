#pragma once
#include "Base.h"
#include "Mathematics.h"
#include <string>

PTR( Drawer );
PTR( Image );

class Drawer : public Base {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }

public:
	Drawer( const char* directory );
	virtual ~Drawer( );

public:
	void update( );

public:
	void waitForSync( );
	void drawFPS( );
	void drawBox( float x1, float y1, float x2, float y2, int color, bool fillflag );
	void drawCircle( float x, float y, float r, int color, bool fillflag );
	void drawLine( float x1, float y1, float x2, float y2, int color );
	void drawString( float x, float y, const char* str, unsigned int color );
	void drawFormatString( float x, float y, unsigned int color, const char* str, ... );
	// ’†‰›‘µ‚¦
	void drawFormatStringCenter( float x, float y, unsigned int color, const char* str, ... );

public:
	void drawSphere( const Vector& pos, float radius, int div_num, unsigned int color = 0xff0000, bool fillflag = false );

public:
	void flip( );

public:
	ImagePtr getImage( const char* file_name );

private:
	std::string _directory;
	int _refresh_count;
	int _start_time;
	int _frame_count;
	float _fps;
};