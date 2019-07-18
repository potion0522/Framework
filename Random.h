#pragma once
#include "Task.h"
#include <string>

/*******************************************

	�����Z���k�c�C�X�^�@(����)�𗘗p���āA
	�֐����킩��₷�������N���X

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