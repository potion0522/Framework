#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( Model );
PTR( Image );
PTR( ModelData );

/*

	model�̐��ɂ����DrawPolygon3D���d����������Ȃ�
	10000�|���S���`�悷��̂ɁA1��DrawPolygon3D���ĂԂ̂ƁA10000��DrawPolygon3D���ĂԂƂł͌�҂̕����d������

*/

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
	void setTexture( ImageConstPtr texture );
	void setTransparent( bool flag );

public:
	void draw( const Vector &pos, const Matrix &mat = Matrix( ) ) const;
	void draw( ) const;

private:
	bool _transparent;
	ImageConstPtr _texture;
	ModelDataPtr _model;
};

