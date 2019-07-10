#pragma once
#include "smart_ptr.h"

PTR( InputString );

class InputString {
friend
	class Keyboard;

private:
	InputString( const int buf_size );

public:
	virtual ~InputString( );

public:
	void setStr( const char* str );
	const char* getStr( ) const;
	bool isActive( ) const;
	void draw( int x, int y ) const;

private:
	const int BUF_SIZE;
	char* _buf;
	int _handle;
};

