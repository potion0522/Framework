#pragma once
#include "smart_ptr.h"

PTR( Task );

class Task {
public:
	Task( ) { };
	virtual ~Task( ) { };

	virtual void finalize( ) { };
	virtual void initialize( ) { };
	virtual void update( ) = 0;
};