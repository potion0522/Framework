#pragma once
#include "Light.h"
#include "smart_ptr.h"

PTR( DirectionalLight );

class DirectionalLight : public Light {
public:
	DirectionalLight( const Vector& dir );
	virtual ~DirectionalLight( );

private:
	Vector _dir;
};

