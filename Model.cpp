#include "Model.h"
#include "DxLib.h"
#include "Image.h"
#include <array>

class ModelData {
public:
	unsigned int _polygon_num;
	VERTEX3D* origin;

	// •`‰æ—p
	VERTEX3D* view;
};

Model::Model( ) :
_transparent( true ) {
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
	DrawPolygon3D( _model->view, _model->_polygon_num, _texture->getHandle( ), _transparent );
}