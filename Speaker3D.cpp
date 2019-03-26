#include "Speaker3D.h"
#include "DxLib.h"

Speaker3D::Speaker3D( int handle ) :
Speaker( handle ) {
}

Speaker3D::~Speaker3D( ) {
}

void Speaker3D::setPosition( const Vector& pos ) {
	Set3DPositionSoundMem( VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ), _handle );
}

void Speaker3D::setRange( const float& range ) {
	Set3DRadiusSoundMem( range, _handle );
}
