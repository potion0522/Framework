#include "PointLight.h"
#include "DxLib.h"

PointLight::PointLight( const Vector& pos, float range, float atten0, float atten1 ) :
Light( pos, range, atten0, atten1 ),
_pos( pos ) {
}

PointLight::~PointLight( ) {
}

void PointLight::setPosition( const Vector& pos ) {
	_pos = pos;
	SetLightPositionHandle( _handle, VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ) );
}