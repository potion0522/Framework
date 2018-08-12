#pragma once
#include "Vector.h"

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