#pragma once
#include "Base.h"
#include "smart_ptr.h"
#include "Vector.h"
#include <string>

PTR( Camera );

class Camera : public Base {
public:
	static CameraPtr getTask( );
	static std::string getTag( );

public:
	Camera( );
	virtual ~Camera( );

public:
	void initialize( );
	void finalize( );
	void update( );

public:
	void setCameraUp( Vector up );
	void setCamera( Vector pos, Vector target );

private:
	Vector _camera_up;
};

