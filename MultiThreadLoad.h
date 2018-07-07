#pragma once
#include "smart_ptr.h"
#include <string>
#include <array>

PTR( MultiThreadLoad );


class MultiThreadLoad {
public:
	MultiThreadLoad( std::string message );
	MultiThreadLoad( );
	virtual ~MultiThreadLoad( );

public:
	void update( );
	void setMaxLength( float max );

private:
	bool _flag;
	float _max;
	int _cnt;
	int _font_handle;
	std::string _message;
};

