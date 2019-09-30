#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

/*******************************************

	’¸“_‚ð’¼‘Å‚¿‚µ‚Äƒ|ƒŠƒSƒ“‚ð•`‰æ‚·‚éƒNƒ‰ƒX

*******************************************/

PTR( Model );
PTR( Image );
PTR( ModelData );

class Model {
public:
	struct Color {
		int r;
		int g;
		int b;
		int a;

		Color( ) : 
		r( 255 ),
		g( 255 ),
		b( 255 ),
		a( 255 ) {
		}

		Color( int in_r, int in_g, int in_b, int in_a ) :
		r( in_r ),
		g( in_g ),
		b( in_b ),
		a( in_a ) {
		}
	};

	struct Vertex {
		Vector pos;
		Vector norm;
		float u;
		float v;
		Color dif;
		Color spc;

		Vertex( ) :
		pos( Vector( ) ),
		norm( Vector( ) ),
		u( 0 ),
		v( 0 ),
		dif( ),
		spc( ) {
		};

		Vertex( const Vector& in_pos, float in_u, float in_v, const Vector& in_norm, const Color& in_dif = Color( ), const Color& in_spc = Color( 0, 0, 0, 0 ) ) :
		pos( in_pos ),
		u( in_u ),
		v( in_v ),
		norm( in_norm ),
		dif( in_dif ),
		spc( in_spc ) {
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
	void setAlpha( int alpha );
	void setUV( int vertex_num, float u, float v );

public:
	void draw( const Vector &pos, const Matrix &mat = Matrix( ) ) const;
	void draw( ) const;

private:
	bool _transparent;
	ImageConstPtr _texture;
	ModelDataPtr _model;
};

