#include "Camera.h"
#include "Manager.h"
#include "DxLib.h"

CameraPtr Camera::getTask( ) {
	return std::dynamic_pointer_cast< Camera >( Manager::getInstance( )->getTask( getTag( ) ) );
}

std::string Camera::getTag( ) {
	return "CAMERA";
}

Camera::Camera( ) {
	_camera_up = Vector( 0, 1, 0 );
}

Camera::~Camera( ) {
}

void Camera::initialize( ) {
}

void Camera::finalize( ) {
}

void Camera::update( ) {
}

void Camera::setCameraUp( Vector up ) {
	_camera_up = up;
}

void Camera::setCamera( Vector pos, Vector target ) {
	VECTOR camera_pos = VECTOR( );
	camera_pos.x = ( float )pos.x;
	camera_pos.y = ( float )pos.y;
	camera_pos.z = ( float )pos.z;

	VECTOR target_pos = VECTOR( );
	target_pos.x = ( float )target.x;
	target_pos.y = ( float )target.y;
	target_pos.z = ( float )target.z;

	VECTOR camera_up = VECTOR( );
	camera_up.x = ( float )_camera_up.x;
	camera_up.y = ( float )_camera_up.y;
	camera_up.z = ( float )_camera_up.z;

	SetCameraPositionAndTargetAndUpVec( camera_pos, target_pos, camera_up );
}