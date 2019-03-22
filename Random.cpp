#include "Random.h"
#include "Manager.h"
#include "MersenneTwister.h"

RandomPtr Random::getTask( ) {
	return std::dynamic_pointer_cast< Random >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Random::Random( ) {
	init_genrand( ( unsigned int )time( NULL ) );
}

Random::~Random( ) {
}

long Random::getRand( long min, long max ) const {
	if ( min == max &&
		 min == 0 && max == 0 ) {
		return genrand_int31( );
	}
	return ( min + ( genrand_int31( ) % ( max + 1 - min ) ) );
}