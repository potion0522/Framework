#include "Model.h"
#include "DxLib.h"
#include "Image.h"
#include "Screen.h"
#include <array>

STRUCT_PTR( MaterialScope );

class ModelData {
public:
	unsigned int _polygon_num;
	VERTEX3D* origin;

	// •`‰æ—p
	VERTEX3D* view;
};

struct MaterialData {
friend MaterialScope;

private:
	Model::Material mat;

public:
	MaterialData( const Model::Material& mat ) :
	mat( mat ) {
	}
};

struct MaterialScope {
private:
	MaterialDataConstPtr data;

public:
	MaterialScope( MaterialDataConstPtr mat ) :
	data( mat ) {
	}

	~MaterialScope( ) {
		SetMaterialUseVertDifColor( TRUE );
		SetMaterialUseVertSpcColor( TRUE );
	}

	void apply( ) {
		MATERIALPARAM param;
		param.Diffuse  = GetColorF( data->mat.dif.r, data->mat.dif.g, data->mat.dif.b, data->mat.dif.a );
		param.Ambient  = GetColorF( data->mat.amb.r, data->mat.amb.g, data->mat.amb.b, data->mat.amb.a );
		param.Specular = GetColorF( data->mat.spc.r, data->mat.spc.g, data->mat.spc.b, data->mat.spc.a );
		param.Emissive = GetColorF( data->mat.emi.r, data->mat.emi.g, data->mat.emi.b, data->mat.emi.a );

		SetMaterialUseVertDifColor( FALSE );
		SetMaterialUseVertSpcColor( FALSE );
		SetMaterialParam( param );
	}
};

Model::Model( ) :
_transparent( true ),
_texture_type( TEXTURE_TYPE_IMAGE ) {
	_model = ModelDataPtr( new ModelData );
}

Model::~Model( ) {
	delete [ ] _model->origin;
	delete [ ] _model->view;
}

void Model::alloc( int polygon_num ) {
	_model->_polygon_num = polygon_num;
	_model->origin = new VERTEX3D[ polygon_num * 3 ];
	_model->view   = new VERTEX3D[ polygon_num * 3 ];
}

void Model::setVertex( int vertex_num, Vertex in_vertex ) {
	VERTEX3D vertex = VERTEX3D( );
	VECTOR pos  = VGet( ( float )in_vertex.pos.x , ( float )in_vertex.pos.y , ( float )in_vertex.pos.z );
	VECTOR norm = VGet( ( float )in_vertex.norm.x, ( float )in_vertex.norm.y, ( float )in_vertex.norm.z );
	vertex.pos = pos;
	vertex.u = in_vertex.u;
	vertex.v = in_vertex.v;
	vertex.norm = norm;
	vertex.dif = GetColorU8( in_vertex.dif.r, in_vertex.dif.g, in_vertex.dif.b, in_vertex.dif.a );
	vertex.spc = GetColorU8( in_vertex.spc.r, in_vertex.spc.g, in_vertex.spc.b, in_vertex.spc.a );

	_model->origin[ vertex_num ] = vertex;
	_model->view  [ vertex_num ] = vertex;
}

void Model::setTexture( ImageConstPtr texture ) {
	_image = texture;
	_texture_type = TEXTURE_TYPE_IMAGE;
}

void Model::setTexture( ScreenConstPtr texture ) {
	_screen = texture;
	_texture_type = TEXTURE_TYPE_SCREEN;
}

void Model::setTransparent( bool flag ) {
	_transparent = flag;
}

void Model::setAlpha( int alpha ) {
	for ( int i = 0; i < ( int )_model->_polygon_num * 3; i++ ) {
		_model->origin[ i ].dif.a = alpha;
		_model->view  [ i ].dif.a = alpha;
	}
}

void Model::setUV( int vertex_num, float u, float v ) {
	VERTEX3D vertex = _model->origin[ vertex_num ];
	vertex.u = u;
	vertex.v = v;

	_model->origin[ vertex_num ] = vertex;
	_model->view  [ vertex_num ] = vertex;
}

void Model::setMaterial( const Material& material ) {
	_material = MaterialDataPtr( new MaterialData( material ) );
}

void Model::draw( const Vector &pos, const Matrix &mat ) const {
	Matrix trans_matrix = Matrix::makeTransformTranslation( pos );
	Matrix all_matrix   = mat * trans_matrix;

	MATRIX all_matrix_dxlib;
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			all_matrix_dxlib.m[ i ][ j ]   = ( float )all_matrix.matrix[ i ][ j ];
		}
	}

	for ( int i = 0; i < ( int )_model->_polygon_num * 3; i++ ) {
		_model->view[ i ].pos  = VTransform( _model->origin[ i ].pos , all_matrix_dxlib );
		_model->view[ i ].norm = VTransformSR( _model->origin[ i ].norm, all_matrix_dxlib );
	}

	draw( );
}

void Model::draw( ) const {
	MaterialScopePtr mat_scope;
	if ( _material ) {
		mat_scope = MaterialScopePtr( new MaterialScope( _material ) );
		mat_scope->apply( );
	}

	DrawPolygon3D( 
		_model->view,
		_model->_polygon_num,
		( _texture_type == TEXTURE_TYPE_IMAGE ? _image->getHandle( ) : _screen->getHandle( ) ),
		_transparent );
}