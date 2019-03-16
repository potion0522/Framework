#pragma once
#include "Base.h"
#include <string>

PTR( Random );

class Random : public Base {
public:
	static RandomPtr getTask( );
	static std::string getTag( ) { return "RANDOM"; }

public:
	Random( );
	virtual ~Random( );

public:
	void initialize( ) { };
	void finalize( ) { };
	void update( ) { };

public:
	long getRand( long min = 0, long max = 0 ) const;
};