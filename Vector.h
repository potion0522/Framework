#pragma once
#include <math.h>

struct Vector {

	double x;
	double y;
	double z;

	Vector( ) :
		x( 0 ),
		y( 0 ),
		z( 0 ) {
	}

	Vector( double input_x, double input_y, double input_z = 0 ) :
		x( input_x ),
		y( input_y ),
		z( input_z ) {
	}

	virtual ~Vector( ) {
	}

	// ‘«‚µZ
	inline Vector add( const Vector& vec ) const {
		return Vector( 
			x + vec.x,
			y + vec.y,
			z + vec.z );
	}
	inline Vector operator+( const Vector& vec ) const {
		return add( vec );
	}
	inline Vector operator+=( const Vector& vec ) {
		*this = *this + vec;
		return *this;
	}

	// ˆø‚«Z
	inline Vector sub( const Vector& vec ) const {
		return Vector( 
			this->x - vec.x,
			this->y - vec.y,
			this->z - vec.z );
	}
	inline Vector operator-( const Vector& vec ) const {
		return sub( vec );
	}
	inline Vector operator-=( const Vector& vec ) {
		*this = *this - vec;
		return *this;
	}

	// Š|‚¯Z
	inline Vector multiply( const double& num ) const {
		return Vector( 
			x * num,
			y * num,
			z * num );
	}
	inline Vector operator*( const double& num ) const {
		return multiply( num );
	}
	inline Vector operator*=( const double& num ) {
		*this = *this * num;
		return *this;
	}

	// ”äŠr ==
	inline bool operator==( const Vector& vec ) const {
		return ( 
			x == vec.x &&
			y == vec.y &&
			z == vec.z );
	}

	// ”äŠr !=
	inline bool operator!=( const Vector& vec ) const {
		return (
			x != vec.x ||
			y != vec.y ||
			z != vec.z );
	}

	// ‹——£‚ğ•Ô‚·
	inline double getLength( ) const {
		double num[ 3 ] = { fabs( x ), fabs( y ), fabs( z ) };
		double max = num[ 0 ];
		for ( int i = 1; i < 3; i++ ) {
			if ( max < num[ i ] ) {
				max = num[ i ];
			}
		}
		if ( max == 0.0 ) {
			return 0;
		}

		// ’´‰ß‚µ‚È‚¢‚æ‚¤‚É¬”“_‚ğ‚ğ‚¸‚ç‚·
		double x = this->x / max;
		double y = this->y / max;
		double z = this->z / max;

		return sqrt( x * x + y * y + z * z ) * max;
	}

	// ‹——£‚ğ•Ô‚·(sqrt‚É‚æ‚é‘¬“x’á‰º‚ğ–h‚®)
	inline double getLength2( ) const {
		return x * x + y * y + z * z;
	}

	// ³‹K‰»
	inline Vector normalize( ) const {
		double len = getLength( );
		Vector normal = Vector( x / len, y / len, z / len );

		return normal;
	}

	// “àÏ
	inline double dot( const Vector& vec ) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}

	// ŠOÏ 3D
	inline Vector cross( const Vector& vec ) const {
		return Vector(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		);
	}

	// ŠOÏ 2D ( •Ô‚è’l‚ÍsinƒÆ )
	inline double cross2D( const Vector& vec ) const {
		return x * vec.y - vec.x * y;
	}
};