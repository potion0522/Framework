#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Mathematics.h"
#include <string>
/*******************************************

3D‹óŠÔ‚ÌƒJƒƒ‰‚ğŠÇ—‚·‚éƒNƒ‰ƒX

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
	void setNearFar( float camera_near, float camera_far );
	void setCameraUp( Vector up );
	void setCamera( Vector pos, Vector target );

private:
	Vector _camera_up;
};

