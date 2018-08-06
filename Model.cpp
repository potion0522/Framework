#include "Model.h"
#include "DxLib.h"
#include "Image.h"
#include <array>

class ModelData {
public:
	unsigned int _polygon_num;
	VERTEX3D *vertex;
};

Model::Model( ) {
	_model = ModelDataPtr( new ModelData );
}

Model::~Model( ) {
	delete [ ] _model->vertex;
}

void Model::setPolygon( int num ) {
	_model->_polygon_num = num;
	_model->vertex = new VERTEX3D[ num * 3 ];
}

void Model::setVertex( int vertex_num, Vertex in_vertex ) {
	VERTEX3D vertex = VERTEX3D( );
	VECTOR pos = VGet( ( float )in_vertex.pos.x, ( float )in_vertex.pos.y, ( float )in_vertex.pos.z );
	VECTOR norm = VGet( ( float )in_vertex.norm.x, ( float )in_vertex.norm.y, ( float )in_vertex.norm.z );
	vertex.pos = pos;
	vertex.u = in_vertex.u;
	vertex.v = in_vertex.v;
	vertex.norm = norm;
	vertex.dif = GetColorU8( 255, 255, 255, 255 );

	_model->vertex[ vertex_num ] = vertex;
}

void Model::setImage( ImageConstPtr image ) {
	_image = image;
}

void Model::draw( ) const {
	DrawPolygon3D( _model->vertex, _model->_polygon_num, _image->getHandle( ), FALSE );
}