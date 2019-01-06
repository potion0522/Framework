#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( Model );
PTR( Image );
PTR( ModelData );

class Model {
public:
	struct Vertex {
		Vector pos;
		Vector norm;
		float u;
		float v;

		Vertex( ) :
		pos( Vector( ) ),
		norm( Vector( ) ),
		u( 0 ),
		v( 0 ){
		};

		Vertex( Vector _pos, float _u, float _v, Vector _norm ) :
		pos( _pos ),
		u( _u ),
		v( _v ),
		norm( _norm ) {
		}
	};

public:
	Model( );
	virtual ~Model( );

public:
	void alloc( int polygon_num );
	void setVertex( int vertex_num, Vertex in_vertex );
	void setImage( ImageConstPtr image );

public:
	void draw( const Vector &pos, const Matrix &mat = Matrix( ) ) const;
	void draw( ) const;

private:
	ImageConstPtr _image;
	ModelDataPtr _model;
};

