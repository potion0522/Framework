#include "ModelMV1.h"
#include "DxLib.h"
#include <assert.h>


ModelMV1::ModelMV1( ) :
_handle( -1 ) {
}

ModelMV1::~ModelMV1( ) {
	MV1DeleteModel( _handle );
}

void ModelMV1::load( const char* path ) {
	_handle = MV1LoadModel( path );
	bool load_model_mv1 = ( _handle != -1 );
	assert( load_model_mv1 );

	MV1SetupReferenceMesh( _handle, -1, TRUE ); // モデルのオリジナルの情報を構築

	// マテリアルの設定
	int num = MV1GetMaterialNum( _handle );
	for ( int i = 0; i < num; i++ ) {
		MV1SetMaterialDifColor( _handle, i, GetColorF( 0.2f, 0.2f, 0.2f, 1.0f ) );
		MV1SetMaterialAmbColor( _handle, i, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) );
		MV1SetMaterialSpcColor( _handle, i, GetColorF( 0.0f, 0.0f, 0.0f, 1.0f ) );
		MV1SetMaterialEmiColor( _handle, i, GetColorF( 0.5f, 0.5f, 0.5f, 1.0f ) );
	}

	MV1_REF_POLYGONLIST list = MV1GetReferenceMesh( _handle, -1, TRUE );
	VECTOR max = list.MaxPosition;
	VECTOR min = list.MinPosition;

	_size = Vector( max.x, max.y, max.z ) - Vector( min.x, min.y, min.z );
}

void ModelMV1::setTexture( const char* path, int mat_idx ) {
	int graph_handle = LoadGraph( path );
	bool load_texture = ( graph_handle != -1 );
	assert( load_texture );
	MV1SetTextureGraphHandle( _handle, mat_idx, graph_handle, TRUE );
}

void ModelMV1::setDifMaterialColor( int mat_idx, float r, float g, float b, float a ) {
	MV1SetMaterialDifColor( _handle, mat_idx, GetColorF( r, g, b, a ) );
}

Vector ModelMV1::getOriginMeterSize( ) const {
	return _size;
}

void ModelMV1::draw( const Vector& pos, const Matrix& mat ) const {
	Matrix all_matrix = mat.multiply( Matrix::makeTransformTranslation( pos ) );
	MATRIX dxlib_matrix;
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			dxlib_matrix.m[ i ][ j ] = ( float )all_matrix.matrix[ i ][ j ];
		}
	}

	MV1SetMatrix( _handle, dxlib_matrix );

	draw( );
}

void ModelMV1::draw( ) const {
	MV1DrawModel( _handle );
}