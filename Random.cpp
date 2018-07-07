#include "Random.h"
#include "MersenneTwister.h"
#include "Manager.h"
#include <time.h>

const unsigned long RANGE_MAX_ULONG = 0xffffffff;
const long RANGE_MAX_LONG = 0x7fffffff;

RandomPtr Random::getTask( ) {
	return std::dynamic_pointer_cast< Random >( Manager::getInstance( )->getTask( getTag( ) ) );
}

std::string Random::getTag( ) {
	return "RANDOM";
}

Random::Random( ) {
	init_genrand( ( unsigned int )time( NULL ) );
}

Random::~Random( ) {
}

void Random::initialize( ) {
}

void Random::update( ) {
}

void Random::setIgnore( unsigned long ignore ) {
	_ignore_long.push_back( ignore );
}

void Random::setIgnore( double ignore ) {
	_ignore_double.push_back( ignore );
}

void Random::resetIgnore( ) {
	std::vector< unsigned long >( ).swap( _ignore_long );
	std::vector< double >( ).swap( _ignore_double );
}

unsigned long Random::getInt32( ) const {
	unsigned long num = genrand_int32( );

	if ( isReplay( num ) ) {
		return getInt32( );
	} else {
		return num;
	}
}

unsigned long Random::getInt32( unsigned long range_min, unsigned long range_max ) const {
	unsigned long num = genrand_int32( ) % ( range_max - range_min + 1 ) + range_min;

	if ( isReplay( num ) ) {
		return getInt32( range_min, range_max );
	} else {
		return num;
	}
}

long Random::getInt31( ) const {
	long num = genrand_int31( );

	if ( isReplay( ( unsigned long )num ) ) {
		return getInt31( );
	} else {
		return num;
	}
}

double Random::getRealOne( ) const {
	double num = genrand_real1( );

	if ( isReplay( num ) ) {
		return getRealOne( );
	} else {
		return num;
	}
}

double Random::getRealTwo( ) const {
	double num = genrand_real2( );

	if ( isReplay( num ) ) {
		return getRealTwo( );
	} else {
		return num;
	}
}

double Random::getRealThree( ) const {
	double num = genrand_real3( );

	if ( isReplay( num ) ) {
		return getRealThree( );
	} else {
		return num;
	}
}

double Random::getRes53( ) const {
	double num = genrand_res53( );

	if ( isReplay( num ) ) {
		return getRes53( );
	} else {
		return num;
	}
}

bool Random::isReplay( unsigned long num ) const {
	for ( unsigned long i = 0; i < ( unsigned long )_ignore_long.size( ); i++ ) {
		if ( num != _ignore_long[ i ] ) {
			continue;
		}
		return true;
	}
	return false;
}

bool Random::isReplay( double num ) const {
	// ¬”‘æŽOˆÊ‚Ü‚Å‚Ì‹ßŽ—’l‚Å”»’è
	for ( unsigned long i = 0; i < ( unsigned long )_ignore_double.size( ); i++ ) {
		if ( ( int )( num * 1000 ) != ( int )( _ignore_double[ i ] * 1000 ) ) {
			continue;
		}
		return true;
	}
	return false;
}