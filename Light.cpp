#include "Light.h"
#include "DxLib.h"


Light::Light( const Vector& dir ) {
	VECTOR dir_dx = VGet( ( float )dir.x, ( float )dir.y, ( float )dir.z );
	_handle = CreateDirLightHandle( dir_dx );
	_type = LIGHT_TYPE_DIRECTION;
}

Light::Light( const Vector& pos, float range, float atten0, float atten1 ) {
	VECTOR pos_dx = VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z );
	_handle  = CreatePointLightHandle( pos_dx, range, atten0, atten1, 0.0f );
	_type = LIGHT_TYPE_POINT;
}

Light::Light( const Vector& pos, const Vector& dir, float out_angle, float in_angle, float range, float atten0, float atten1 ) {
	VECTOR pos_dx = VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z );
	VECTOR dir_dx = VGet( ( float )dir.x, ( float )dir.y, ( float )dir.z );
	_handle = CreateSpotLightHandle( pos_dx, dir_dx, out_angle, in_angle, range, atten0, atten1, 0.0f );
	_type = LIGHT_TYPE_SPOT;
}

Light::~Light( ) {
	DeleteLightHandle( _handle );
}

void Light::setEnable( bool flag ) {
	int flag_int = ( flag ? TRUE : FALSE );
	SetLightEnableHandle( _handle, flag_int );
}

bool Light::isEnabled( ) const {
	return ( TRUE == GetLightEnableHandle( _handle ) );
}

Light::LIGHT_TYPE Light::getType( ) const {
	return _type;
}
