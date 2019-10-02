#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( ModelMV1 );

class ModelMV1 {
public:
	ModelMV1( );
	virtual ~ModelMV1( );

public:
	void load( const char* path );
	void setTexture( const char* path, int mat_idx = 0 );
	void setPos( const Vector& pos );
	void setScale( const Vector& scale );
	void setRotate( const Vector& radian );
	void setDifMaterialColor( int mat_idx, float r, float g, float b, float a );
	Vector getOriginMeterSize( ) const;
	void draw( ) const;

private:
	int _handle;
	Vector _size;
};
