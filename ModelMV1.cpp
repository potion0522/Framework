#include "ModelMV1.h"
#include "DxLib.h"
#include <assert.h>


ModelMV1::ModelMV1( ) :
_handle( -1 ) {
}

ModelMV1::~ModelMV1( ) {
}

void ModelMV1::load( const char* path ) {
	_handle = MV1LoadModel( path );
	bool load_model_mv1 = ( _handle != -1 );
	assert( load_model_mv1 );

	// ƒ}ƒeƒŠƒAƒ‹‚Ìİ’è
	int num = MV1GetMaterialNum( _handle );
	for ( int i = 0; i < num; i++ ) {
		MV1SetMaterialDifColor( _handle, i, GetColorF( 0.2f, 0.2f, 0.2f, 1.0f ) );
		MV1SetMaterialAmbColor( _handle, i, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) );
		MV1SetMaterialSpcColor( _handle, i, GetColorF( 0.0f, 0.0f, 0.0f, 1.0f ) );
		MV1SetMaterialEmiColor( _handle, i, GetColorF( 0.5f, 0.5f, 0.5f, 1.0f ) );
	}

}

void ModelMV1::setTexture( const char* path, int mat_idx ) {
	int graph_handle = LoadGraph( path );
	bool load_texture = ( graph_handle != -1 );
	assert( load_texture );
	MV1SetTextureGraphHandle( _handle, mat_idx, graph_handle, TRUE );
}

void ModelMV1::setPos( const Vector& pos ) {
	MV1SetPosition( _handle, VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ) );
}

void ModelMV1::setScale( const Vector& scale ) {
	MV1SetScale( _handle, VGet( ( float )scale.x, ( float )scale.y, ( float )scale.z ) );
}

void ModelMV1::setRotate( const Vector& radian ) {
	MV1SetRotationXYZ( _handle, VGet( ( float )radian.x, ( float )radian.y, ( float )radian.z ) );
}

void ModelMV1::setDifMaterialColor( int mat_idx, float r, float g, float b, float a ) {
	MV1SetMaterialDifColor( _handle, mat_idx, GetColorF( r, g, b, a ) );
}

void ModelMV1::draw( ) const {
	MV1DrawModel( _handle );
}