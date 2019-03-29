#include "DirectionalLight.h"
#include "DxLib.h"

DirectionalLight::DirectionalLight( const Vector& dir ) :
Light( dir ),
_dir( dir ) {
}

DirectionalLight::~DirectionalLight( ) {
}
