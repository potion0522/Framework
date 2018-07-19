#pragma once
#include "Base.h"
#include "Vector.h"
#include <vector>
#include <string>

PTR( Drawer );
PTR( Image );

class Drawer : public Base {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }

public:
	Drawer( std::string image_path );
	virtual ~Drawer( );

public:
	void initialize( );
	void finalize( );
	void update( );

public:
	// 2D関係
	void drawGraph( int x, int y, int handle, bool transflag );
	void drawGraph( float x, float y, int handle, bool transflag );
	void drawRotaGraph( float x, float y, double exrate, double angle, int handle, bool transflag );
	void drawRectGraph( float screen_x, float screen_y, int lx, int ly, int width, int height, int handle, bool transflag, bool turnflag = false );
	// x1,y1 左上頂点座標、x2,y2 右下頂点座標
	void drawExtendGraph( float x1, float y1, float x2, float y2, int handle, bool transflag );
	void drawBox( float x1, float y1, float x2, float y2, int color, bool fillflag );
	void drawCircle( float x, float y, float r, int color, bool fillflag );
	void drawLine( float x1, float y1, float x2, float y2, int color );
	void drawString( float x, float y, std::string str, unsigned int color );
	void drawFormatString( float x, float y, unsigned int color, const char *str, ... );
	// 中央揃え
	void drawFormatStringCenter( float x, float y, unsigned int color, const char *str, ... );

public:
	// 3D関係
	// 描画座標、画像中心X、画像中心Y、サイズ、アングル、ハンドル、透明度有効化
	void drawBillBoard3D( Vector pos, float cx, float cy, float size, float angle, int handle, bool transflag );
	void drawShere3D( Vector pos, float r, int div_num, int dif_color, int spc_color, bool fillflag );

public:
	void setGraphAlpha( int alpha );

public:
	void flip( );

private:
	void checkHandle( int handle );

public:
	int getImage( std::string file_name ) const;
	int getImageWidth( std::string file_name ) const;
	int getImageHeight( std::string file_name ) const;

private:
	ImagePtr _image;
};