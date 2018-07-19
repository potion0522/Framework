#include "Drawer.h"
#include "DxLib.h"
#include "Manager.h"
#include "Image.h"
#include <errno.h>
#include <assert.h>

DrawerPtr Drawer::getTask( ) {
	return std::dynamic_pointer_cast< Drawer >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Drawer::Drawer( std::string image_path ) {
	_image = ImagePtr( new Image( image_path ) );
}

Drawer::~Drawer( ) {
}

void Drawer::initialize( ) {
}

void Drawer::finalize( ) {
}

void Drawer::update( ) {

}

void Drawer::drawGraph( int x, int y, int handle, bool transflag ) {
	checkHandle( handle );
	DrawGraph( x, y, handle, transflag );
}

void Drawer::drawGraph( float x, float y, int handle, bool transflag ) {
	checkHandle( handle );
	DrawGraphF( x, y, handle, transflag );
}

void Drawer::drawRotaGraph( float x, float y, double exrate, double angle, int handle, bool transflag ) {
	checkHandle( handle );
	DrawRotaGraphF( x, y, exrate, angle, handle, transflag );
}

void Drawer::drawRectGraph( float screen_x, float screen_y, int lx, int ly, int width, int height, int handle, bool transflag, bool turnflag ) {
	checkHandle( handle );
	DrawRectGraphF( screen_x, screen_y, lx, ly, width, height, handle, transflag, turnflag );
}

void Drawer::drawExtendGraph( float x1, float y1, float x2, float y2, int handle, bool transflag ) {
	checkHandle( handle );
	DrawExtendGraphF( x1, y1, x2, y2, handle, transflag );
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

void Drawer::drawString( float x, float y, std::string str, unsigned int color ) {
	DrawStringF( x, y, str.c_str( ), color );
}

void Drawer::drawFormatString( float x, float y, unsigned int color, const char *str, ... ) {

	const int BUF_MAX = 1024;
	char buf[ BUF_MAX ] = { };

	va_list ap;
	// str‚æ‚èŒã‚ë‚Ìˆø”‚ðŠi”[
	va_start( ap, str );

	// Ši”[‚µ‚½ˆø”‚ðbuf‚É’Ç‰Á
	vsprintf_s( buf, BUF_MAX, str, ap );

	// ƒŠƒXƒg‚ðƒNƒŠƒA
	va_end( ap );
	DrawStringF( x, y, buf, color );
}

void Drawer::drawFormatStringCenter( float x, float y, unsigned int color, const char *str, ... ) {
	const int BUF_MAX = 1024;
	char buf[ BUF_MAX ] = { };

	va_list ap;
	// str‚æ‚èŒã‚ë‚Ìˆø”‚ðŠi”[
	va_start( ap, str );

	// Ši”[‚µ‚½ˆø”‚ðbuf‚É’Ç‰Á
	vsprintf_s( buf, BUF_MAX, str, ap );

	// ƒŠƒXƒg‚ðƒNƒŠƒA
	va_end( ap );

	int len = ( int )strlen( buf );
	float gap_x = GetDrawStringWidth( buf, len ) / 2.0f;
	DrawStringF( x - gap_x, y, buf, color );
}

void Drawer::drawBillBoard3D( Vector pos, float cx, float cy, float size, float angle, int handle, bool transflag ) {
	VECTOR vec = VECTOR( );
	vec.x = ( float )pos.x;
	vec.y = ( float )pos.y;
	vec.z = ( float )pos.z;

	DrawBillboard3D( vec, cx, cy, size, angle, handle, transflag );
}

void Drawer::drawShere3D( Vector pos, float r, int div_num, int dif_color, int spc_color, bool fillflag ) {
	VECTOR vec = VECTOR( );
	vec.x = ( float )pos.x;
	vec.y = ( float )pos.y;
	vec.z = ( float )pos.z;
	DrawSphere3D( vec, r, div_num, dif_color, spc_color, fillflag );
}

void Drawer::setGraphAlpha( int alpha ) {
	if ( alpha == 0 ) {
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, alpha );
		return;
	}
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );
}

void Drawer::flip( ) {
	ScreenFlip( );
	ClearDrawScreen( );
}

void Drawer::checkHandle( int handle ) {
	errno_t not_find_handle = handle;
	assert( not_find_handle != -1 );
}

int Drawer::getImage( std::string file_name ) const {
	return _image->getImage( file_name );
}

int Drawer::getImageWidth( std::string file_name ) const {
	return _image->getImageWidth( file_name );
}

int Drawer::getImageHeight( std::string file_name ) const {
	return _image->getImageHeight( file_name );
}