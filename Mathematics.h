#pragma once
#include <math.h>

const double PI = 31.4159265;

// ƒxƒNƒgƒ‹ /////////////////////////////////////////////
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



// s—ñ /////////////////////////////////////////////
struct Matrix {
	double matrix[ 4 ][ 4 ];

	Matrix( ) {
		// ’PˆÊs—ñ‚ğ¶¬
		for ( int i = 0; i < 4; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				matrix[ i ][ j ] = 0;
			}

			matrix[ i ][ i ] = 1;
		}
	}

	~Matrix( ) {
	}

	// ƒƒhƒŠƒQƒX‚Ì‰ñ“]Œö®(”CˆÓ²‚Ì‰ñ“]s—ñ‚ğ¶¬)
	inline static Matrix makeTransformRotation( const Vector &in_axis, double radian ) {
		Vector axis = in_axis.normalize( );
		double value = ( 1 - cos( radian ) );
		double value_sin = sin( radian );
		double value_cos = cos( radian );

		Matrix mat;
		mat.matrix[ 0 ][ 0 ] = value_cos + axis.x * axis.x * value;
		mat.matrix[ 0 ][ 1 ] = axis.x * axis.y * value - axis.z * value_sin;
		mat.matrix[ 0 ][ 2 ] = axis.z * axis.x * value + axis.y * value_sin;

		mat.matrix[ 1 ][ 0 ] = axis.x * axis.y * value + axis.z * value_sin;
		mat.matrix[ 1 ][ 1 ] = value_cos + axis.y * axis.y * value;
		mat.matrix[ 1 ][ 2 ] = axis.y * axis.z * value - axis.x * value_sin;

		mat.matrix[ 2 ][ 0 ] = axis.z * axis.x * value - axis.y * value_sin;
		mat.matrix[ 2 ][ 1 ] = axis.y * axis.z * value + axis.x * value_sin;
		mat.matrix[ 2 ][ 2 ] = value_cos + axis.z * axis.z * value;

		return mat;
	}

	inline static Matrix makeTransformScaling( const Vector &in_vec ) {
		Matrix mat;
		mat.matrix[ 0 ][ 0 ] = in_vec.x;
		mat.matrix[ 1 ][ 1 ] = in_vec.y;
		mat.matrix[ 2 ][ 2 ] = in_vec.z;
		return mat;
	}

	inline static Matrix makeTransformTranslation( const Vector &in_vec ) {
		Matrix mat;
		mat.matrix[ 3 ][ 0 ] = in_vec.x;
		mat.matrix[ 3 ][ 1 ] = in_vec.y;
		mat.matrix[ 3 ][ 2 ] = in_vec.z;
		return mat;
	}

	inline Vector multiply( const Vector &in_vec ) const {
		Vector result;
		result.x = in_vec.x * matrix[ 0 ][ 0 ] + in_vec.y * matrix[ 1 ][ 0 ] + in_vec.z * matrix[ 2 ][ 0 ] + 1 * matrix[ 3 ][ 0 ];
		result.y = in_vec.x * matrix[ 0 ][ 1 ] + in_vec.y * matrix[ 1 ][ 1 ] + in_vec.z * matrix[ 2 ][ 1 ] + 1 * matrix[ 3 ][ 1 ];
		result.z = in_vec.x * matrix[ 0 ][ 2 ] + in_vec.y * matrix[ 1 ][ 2 ] + in_vec.z * matrix[ 2 ][ 2 ] + 1 * matrix[ 3 ][ 2 ];
		return result;
	}

	inline Matrix multiply( const Matrix &in_mat ) const {
		Matrix mat;

		for ( int i = 0; i < 4; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				mat.matrix[ i ][ j ] = 0;
				for ( int k = 0; k < 4; k++ ) {
					mat.matrix[ i ][ j ] += matrix[ i ][ k ] * in_mat.matrix[ k ][ j ];
				}
			}
		}

		return mat;
	}

	inline Matrix operator*( const Matrix &in_mat ) const {
		return this->multiply( in_mat );
	}
	inline Matrix operator*=( const Matrix &in_mat ) {
		*this = *this * in_mat;
		return *this;
	}
};