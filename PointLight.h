#pragma once
#include "Light.h"
#include "smart_ptr.h"

PTR( PointLight );

class PointLight : public Light {
public:
	// 位置、影響最大距離、減衰率(+atten)、減衰率2(+atten*頂点までの距離)
	PointLight( const Vector& pos, float range, float atten0, float atten1 );
	virtual ~PointLight( );

public:
	void setPosition( const Vector& pos );

private:
	Vector _pos;
};

