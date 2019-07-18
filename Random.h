#pragma once
#include "Task.h"
#include <string>

/*******************************************

	メルセンヌツイスタ法(乱数)を利用して、
	関数をわかりやすくしたクラス

*******************************************/

PTR( Random );

class Random : public Task {
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