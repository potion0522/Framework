#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

/*******************************************

	’¸“_‚ð’¼‘Å‚¿‚µ‚Äƒ|ƒŠƒSƒ“‚ð•`‰æ‚·‚éƒNƒ‰ƒX

*******************************************/

PTR( Model );
PTR( Image );
PTR( ModelData );
STRUCT_PTR( MaterialData );

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

		Color( int r, int g, int b, int a ) :
		r( r ),
		g( g ),
		b( b ),
		a( a ) {
		}
	};

	struct ColorF {
		float r;
		float g;
		float b;
		float a;

		ColorF( ) :
		r( 1.0f ),
		g( 1.0f ),
		b( 1.0f ),
		a( 1.0f ) {
		}

		ColorF( float r, float g, float b, float a ) :
		r( r ),
		g( g ),
		b( b ),
		a( a ) {
		}
	};

	struct Material {
		ColorF dif;
		ColorF amb;
		ColorF spc;
		ColorF emi;

		Material( ) :
		dif( ColorF( 0.2f, 0.2f, 0.2f, 1.0f ) ),
		amb( ColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ),
		spc( ColorF( 0.0f, 0.0f, 0.0f, 1.0f ) ),
		emi( ColorF( 0.5f, 0.5f, 0.5f, 1.0f ) ) {
		}

		void setDifColor( ColorF dif ) {
			this->dif = dif;
		}
		void setAmbColor( ColorF amb ) {
			this->amb = amb;
		}
		void setSpcColor( ColorF spc ) {
			this->spc = spc;
		}
		void setEmiColor( ColorF emi ) {
			this->emi = emi;
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
	void setMaterial( const Material& material );

public:
	void draw( const Vector &pos, const Matrix &mat = Matrix( ) ) const;
	void draw( ) const;

private:
	bool _transparent;
	MaterialDataPtr _material;
	ImageConstPtr _texture;
	ModelDataPtr _model;
};