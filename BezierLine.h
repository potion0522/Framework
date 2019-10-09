#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include <vector>

PTR( BezierLine );

class BezierLine {
public:
	BezierLine( );
	virtual ~BezierLine( );

public:
	Vector getPoint( double time, const std::vector< Vector >& points ); // time�� 0 �` 1 ���w�肷��
};

