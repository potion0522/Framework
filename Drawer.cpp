#include "Drawer.h"
#include "DxLib.h"
#include "Manager.h"
#include "Image.h"
#include <errno.h>
#include <assert.h>

DrawerPtr Drawer::getTask( ) {
	return std::dynamic_pointer_cast< Drawer >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Drawer::Drawer( std::string image_directory ) :
_image_directory( image_directory ) {
}

Drawer::~Drawer( ) {
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

void Drawer::flip( ) {
	ScreenFlip( );
	ClearDrawScreen( );
}

ImagePtr Drawer::getImage( std::string file_name ) {
	ImagePtr image = ImagePtr( new Image );

	std::string path = _image_directory + "/" + file_name;
	bool success = image->load( path );

	ImagePtr result = image;
	if ( !success ) {
		result = ImagePtr( );
	}

	return result;
}