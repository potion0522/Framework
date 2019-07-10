#include "InputString.h"
#include "DxLib.h"
#include <string.h>

InputString::InputString( const int buf_size ) :
BUF_SIZE( buf_size + 1 ) {
	_buf = new char [ BUF_SIZE ];
	memset( _buf, '\0', sizeof( char ) * BUF_SIZE );

	_handle = MakeKeyInput( buf_size - 2, FALSE, FALSE, FALSE ); // 日本語okなので2バイト引く
	SetActiveKeyInput( _handle );
	SetKeyInputString( _buf, _handle );
}

InputString::~InputString( ) {
	DeleteKeyInput( _handle );
	delete [ ] _buf;
}

void InputString::setStr( const char* str ) {
	strcpy_s( _buf, BUF_SIZE, str );
	SetKeyInputString( _buf, _handle );
}

const char* InputString::getStr( ) const {
	GetKeyInputString( _buf, _handle );
	return _buf;
}

bool InputString::isActive( ) const {
	bool result = false;
	int check = CheckKeyInput( _handle );
	switch ( check ) {
	case 0:
		result = true;
		break;

	case 1:
	case 2:
		result = false;
		break;

	case -1:
		result = false;
		break;
	}

	return result;
}

void InputString::draw( int x, int y ) const {
	DrawKeyInputString( x, y, _handle );
}