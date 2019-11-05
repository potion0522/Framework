#include "Drawer.h"
#include "DxLib.h"
#include "Manager.h"
#include "Image.h"
#include "Movie.h"
#include <errno.h>
#include <assert.h>
#include <stdarg.h>

const int FPS = 30;
const double FRAME_TIME = 1000.0 / FPS;

DrawerPtr Drawer::getTask( ) {
	return std::dynamic_pointer_cast< Drawer >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Drawer::Drawer( const char* directory ) :
_directory( directory ),
_frame_count( 0 ),
_fps( 0.0f ) {
	_start_time = GetNowCount( );
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	// 規定値分の処理が終わった時の時間を計算(30フレーム)
	if ( _frame_count == 0 ) {
		int now_time = GetNowCount( );
		int time = now_time - _start_time;

		_fps = 1000.0f / ( float )time * ( float )FPS;
		_frame_count = 0;
		_start_time = now_time;
	}
	_frame_count = ( _frame_count + 1 ) % FPS;
}

void Drawer::setAlpha( int alpha ) {
	if ( alpha >= 255 ) {
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, alpha );
	} else {
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );
	}
}

void Drawer::waitForSync( ) {
	int now_time = GetNowCount( ); // 実際にかかった時間
	int time = 1000 / FPS * _frame_count + _start_time; // 本来の時間
	int sleep_time = time - now_time;

	if ( sleep_time > 0 ) {
		Sleep( sleep_time );
	}
}

void Drawer::drawFPS( ) {
	this->drawFormatString( 20, 20, 0xff0000, "FPS : %.3f", _fps );
}

void Drawer::drawBox( float x1, float y1, float x2, float y2, int color, bool fillflag ) {
	DrawBoxAA( x1, y1, x2, y2, color, fillflag );
}

void Drawer::drawCircle( float x, float y, float r, int color, bool fillflag ) {
	DrawCircleAA( x, y, r, 32, color, fillflag );
}

void Drawer::drawLine( float x1, float y1, float x2, float y2, int color ) {
	DrawLineAA( x1, y1, x2, y2, color );
}

void Drawer::drawString( float x, float y, const char* str, unsigned int color ) {
	DrawStringF( x, y, str, color );
}

void Drawer::drawFormatString( float x, float y, unsigned int color, const char* str, ... ) {

	const int BUF_MAX = 1024;
	char buf[ BUF_MAX ] = { };

	va_list ap;
	// strより後ろの引数を格納
	va_start( ap, str );

	// 格納した引数をbufに追加
	vsprintf_s( buf, BUF_MAX, str, ap );

	// リストをクリア
	va_end( ap );
	DrawStringF( x, y, buf, color );
}

void Drawer::drawFormatString( float x, float y, unsigned int color, int font_size, const char* str, ... ) {
	const int BUF_MAX = 1024;
	char buf[ BUF_MAX ] = { };

	va_list ap;
	// strより後ろの引数を格納
	va_start( ap, str );

	// 格納した引数をbufに追加
	vsprintf_s( buf, BUF_MAX, str, ap );

	// リストをクリア
	va_end( ap );

	// サイズ変更
	int font_handle;
	if ( _font_handles.count( font_size ) == 0 ) {
		_font_handles[ font_size ] = CreateFontToHandle( NULL, font_size, -1, DX_FONTTYPE_NORMAL );
	}
	font_handle = _font_handles[ font_size ];

	DrawStringFToHandle( x, y, buf, color, font_handle );
}

void Drawer::drawFormatStringCenter( float x, float y, unsigned int color, const char* str, ... ) {
	const int BUF_MAX = 1024;
	char buf[ BUF_MAX ] = { };

	va_list ap;
	// strより後ろの引数を格納
	va_start( ap, str );

	// 格納した引数をbufに追加
	vsprintf_s( buf, BUF_MAX, str, ap );

	// リストをクリア
	va_end( ap );

	int len = ( int )strlen( buf );
	float gap_x = GetDrawStringWidth( buf, len ) / 2.0f;
	DrawStringF( x - gap_x, y, buf, color );
}

void Drawer::drawFormatStringCenter( float x, float y, unsigned int color, int font_size, const char* str, ... ) {
	const int BUF_MAX = 1024;
	char buf[ BUF_MAX ] = { };

	va_list ap;
	// strより後ろの引数を格納
	va_start( ap, str );

	// 格納した引数をbufに追加
	vsprintf_s( buf, BUF_MAX, str, ap );

	// リストをクリア
	va_end( ap );

	// サイズ変更
	int font_handle;
	if ( _font_handles.count( font_size ) == 0 ) {
		_font_handles[ font_size ] = CreateFontToHandle( NULL, font_size, -1, DX_FONTTYPE_NORMAL );
	}
	font_handle = _font_handles[ font_size ];

	int len = ( int )strlen( buf );
	float gap_x = GetDrawStringWidthToHandle( buf, len, font_handle ) / 2.0f;
	DrawStringFToHandle( x - gap_x, y, buf, color, font_handle );
}

float Drawer::getFps( ) const {
	return _fps;
}

int Drawer::getStringWidth( const char* str ) const {
	int len = ( int )strlen( str );
	return GetDrawStringWidth( str, len );
}

int Drawer::getStringWidth( const char* str, int font_size ) const {
	// サイズ変更
	int font_handle;
	if ( _font_handles.count( font_size ) == 0 ) {
		return 0; // フォントハンドルがない
	}

	font_handle = _font_handles.at( font_size );

	int len = ( int )strlen( str );
	return GetDrawStringWidthToHandle( str, len, font_handle );
}

void Drawer::drawSphere( const Vector& pos, float radius, int div_num, unsigned int color, bool fillflag ) {
	VECTOR sphere_pos = VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z );
	DrawSphere3D( sphere_pos, radius, div_num, color, color, fillflag );
}

void Drawer::flip( ) {
	ScreenFlip( );
	ClearDrawScreen( );
}

ImagePtr Drawer::getImage( const char* file_name ) {
	ImagePtr image = ImagePtr( new Image );

	std::string path = _directory + "/" + file_name;
	
	// ファイルがうまく読み込めなかったらエラーを出す
	errno_t load_imagefile = image->load( path.c_str( ) );
	assert( load_imagefile );

	return image;
}

MoviePtr Drawer::getMovie( const char* file_name ) {
	MoviePtr movie = MoviePtr( new Movie );

	std::string path = _directory + "/" + file_name;

	// ファイルがうまく読み込めなかったらエラーを出す
	errno_t load_imagefile = movie->load( path.c_str( ) );
	assert( load_imagefile );

	return movie;
}