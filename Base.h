#pragma once
#include "smart_ptr.h"

PTR( Base );

class Base {
public:
	Base( );
	virtual ~Base( );

	virtual void finalize( );
	virtual void initialize( ) = 0;
	virtual void update( ) = 0;
};