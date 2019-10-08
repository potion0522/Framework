#include "Model.h"
#include "DxLib.h"
#include "Image.h"
#include <array>

STRUCT_PTR( MaterialScope );

class ModelData {
public:
	unsigned int _polygon_num;
	VERTEX3D* origin;

	// •`‰æ—p
	VERTEX3D* view;
};

struct MaterialScope {
	MaterialScope( ) { };
	~MaterialScope( ) {
		MATERIALPARAM param;
		Model::Material mat;
		param.Diffuse  = GetColorF( mat.dif.r, mat.dif.g, mat.dif.b, mat.dif.a );
		param.Ambient  = GetColorF( mat.amb.r, mat.amb.g, mat.amb.b, mat.amb.a );
		param.Specular = GetColorF( mat.spc.r, mat.spc.g, mat.spc.b, mat.spc.a );
		param.Emissive = GetColorF( mat.emi.r, mat.emi.g, mat.emi.b, mat.emi.a );
		SetMaterialParam( param );
	}

	void set( const Model::Material& mat ) {
		MATERIALPARAM param;
		param.Diffuse  = GetColorF( mat.dif.r, mat.dif.g, mat.dif.b, mat.dif.a );
		param.Ambient  = GetColorF( mat.amb.r, mat.amb.g, mat.amb.b, mat.amb.a );
		param.Specular = GetColorF( mat.spc.r, mat.spc.g, mat.spc.b, mat.spc.a );
		param.Emissive = GetColorF( mat.emi.r, mat.emi.g, mat.emi.b, mat.emi.a );
		SetMaterialParam( param );
	}
};

Model::Model( ) :
_transparent( true ),
_set_material( false ),
_material( Model::Material( ) ) {
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
	_texture = texture;
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
	_material = material;
	_set_material = true;
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
	MaterialScopePtr scope;
	if ( _set_material ) {
		scope = MaterialScopePtr( new MaterialScope );
		scope->set( _material );
	}

	DrawPolygon3D( _model->view, _model->_polygon_num, _texture->getHandle( ), _transparent );
}