#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Mathematics.h"
#include <string>
/*******************************************

3D空間のカメラを管理するクラス

*******************************************/

PTR( Camera );

class Camera : public Task {
public:
	static CameraPtr getTask( );
	static std::string getTag( ) { return "CAMERA"; }

public:
	Camera( );
	virtual ~Camera( );

public:
	void initialize( ) { };
	void finalize( ) { };
	void update( ) { };

public:
	// near は 0.1より大きく
	void setNearFar( float camera_near, float camera_far );
	void setCameraUp( Vector up );
	void setCamera( Vector pos, Vector target );
	Vector getCameraForwardDir( ) const;

private:
	Vector _camera_up;
	Vector _pos;
	Vector _target;
};

