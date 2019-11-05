#include "Screen.h"
#include "DxLib.h"

Screen::Scope::Scope( ) {
}

Screen::Scope::~Scope( ) {
	SetDrawScreen( DX_SCREEN_BACK );
}

Screen::Screen( int width, int height ) {
	_handle = MakeScreen( width, height );
}

Screen::~Screen( ) {
}

Screen::Scope Screen::createScope( ) const {
	return Scope( );
}

void Screen::setDrawScreen( const Scope& scope ) const {
	SetDrawScreen( _handle );
	ClearDrawScreen( );
}

int Screen::getHandle( ) const {
	return _handle;
}