#include "SpotLight.h"
#include "DxLib.h"

SpotLight::SpotLight( const Vector& pos, const Vector& dir, float out_angle, float in_angle, float range, float atten0, float atten1 ) :
Light( pos, dir, out_angle, in_angle, range, atten0, atten1 ),
_pos( pos ) {
}

SpotLight::~SpotLight( ) {
}

void SpotLight::setPosition( const Vector& pos ) {
	_pos = pos;
	SetLightPositionHandle( _handle, VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ) );
}