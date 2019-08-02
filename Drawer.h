#pragma once
#include "Task.h"
#include "Mathematics.h"
#include <string>
#include <unordered_map>
/*********************************************************************

	デバッグ用の描画機能、Imageファイルのロードのエラー処理を行う
	FPSを30に固定する機能も保持

**********************************************************************/

PTR( Drawer );
PTR( Image );

class Drawer : public Task {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }

public:
	Drawer( const char* directory );
	virtual ~Drawer( );

public:
	void update( );

public:
	void setAlpha( int alpha );
	void waitForSync( );
	void drawFPS( );
	void drawBox( float x1, float y1, float x2, float y2, int color, bool fillflag );
	void drawCircle( float x, float y, float r, int color, bool fillflag );
	void drawLine( float x1, float y1, float x2, float y2, int color );
	void drawString( float x, float y, const char* str, unsigned int color );
	void drawFormatString( float x, float y, unsigned int color, const char* str, ... );
	void drawFormatString( float x, float y, unsigned int color, int font_size, const char* str, ... );
	// 中央揃え
	void drawFormatStringCenter( float x, float y, unsigned int color, const char* str, ... );
	void drawFormatStringCenter( float x, float y, unsigned int color, int font_size, const char* str, ... );

	float getFps( ) const;
	int getStringWidth( const char* str ) const;
	int getStringWidth( const char* str, int font_size ) const;

public:
	void drawSphere( const Vector& pos, float radius, int div_num, unsigned int color = 0xff0000, bool fillflag = false );

public:
	void flip( );

public:
	ImagePtr getImage( const char* file_name );

private:
	std::string _directory;
	int _start_time;
	int _frame_count;
	float _fps;
	std::unordered_map< int, int > _font_handles;
};