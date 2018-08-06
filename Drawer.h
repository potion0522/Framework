#pragma once
#include "Base.h"
#include "Vector.h"
#include <string>

PTR( Drawer );
PTR( Image );

class Drawer : public Base {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }

public:
	Drawer( std::string image_directory );
	virtual ~Drawer( );

public:
	void update( ) { };

public:
	void drawBox( float x1, float y1, float x2, float y2, int color, bool fillflag );
	void drawCircle( float x, float y, float r, int color, bool fillflag );
	void drawLine( float x1, float y1, float x2, float y2, int color );
	void drawString( float x, float y, std::string str, unsigned int color );
	void drawFormatString( float x, float y, unsigned int color, const char *str, ... );
	// ’†‰›‘µ‚¦
	void drawFormatStringCenter( float x, float y, unsigned int color, const char *str, ... );

public:
	void drawSphere( Vector pos, float radius, int div_num, unsigned int color = 0xff0000, bool fillflag = false );

public:
	void flip( );

public:
	ImagePtr getImage( std::string file_name );

private:
	std::string _image_directory;
};