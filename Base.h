#pragma once
#include "smart_ptr.h"

PTR( Base );

class Base {
public:
	Base( );
	virtual ~Base( );

	virtual void finalize( );
	virtual void initialize( );
	virtual void update( ) = 0;
};