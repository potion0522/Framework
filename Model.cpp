#include "Model.h"
#include "DxLib.h"
#include "Image.h"
#include <array>

class ModelData {
public:
	unsigned int _polygon_num;
	VERTEX3D *origin;

	// •`‰æ—p
	VERTEX3D *view;
};

Model::Model( ) {
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
	vertex.dif = GetColorU8( 255, 255, 255, 255 );

	_model->origin[ vertex_num ] = vertex;
	_model->view  [ vertex_num ] = vertex;
}

void Model::setImage( ImageConstPtr image ) {
	_image = image;
}

void Model::draw( const Vector &pos, const Matrix &mat ) const {
	for ( int i = 0; i < ( int )_model->_polygon_num * 3; i++ ) {
		Vector origin_pos  = Vector( _model->origin[ i ].pos.x, _model->origin[ i ].pos.y, _model->origin[ i ].pos.z );
		Vector origin_norm = Vector( _model->view[ i ].norm.x, _model->view[ i ].norm.y, _model->view[ i ].norm.z );

		Matrix matrix = mat * Matrix::makeTransformTranslation( pos );

		Vector conv_pos  = matrix.multiply( origin_pos  );
		Vector conv_norm = matrix.multiply( origin_norm );

		_model->view[ i ].pos  = VGet( ( float )conv_pos.x , ( float )conv_pos.y , ( float )conv_pos.z  );
		_model->view[ i ].norm = VGet( ( float )conv_norm.x, ( float )conv_norm.y, ( float )conv_norm.z );
	}

	draw( );
}

void Model::draw( ) const {
	DrawPolygon3D( _model->view, _model->_polygon_num, _image->getHandle( ), FALSE );
}