#include "BezierLine.h"

BezierLine::BezierLine( ) {
}

BezierLine::~BezierLine( ) {
}

Vector BezierLine::getPoint( double time, const std::vector< Vector >& points ) {
	int loop_num = ( int )points.size( ) - 1;
	if ( loop_num < 1 ) {
		return Vector( );
	}
	std::vector< Vector > create_points;

	for ( int i = 0; i < loop_num; i++ ) {
		const Vector& point1 = points[ i ];
		const Vector& point2 = points[ i + 1 ];

		Vector line = ( point2 - point1 );
		create_points.push_back( line * time + point1 );
	}

	Vector target_point = create_points.back( );

	// line ‚ª•¡”‚¾‚Á‚½‚çÄ‹N
	if ( create_points.size( ) > 1 ) {
		target_point = getPoint( time, create_points );
	}

	return target_point;
}