#pragma once
#include "Light.h"
#include "smart_ptr.h"

PTR( SpotLight );

class SpotLight : public Light {
public:
	// 位置、角度、ライトの影響角度(0~PI)、ライトの減衰開始角度(0~out_angle)、影響最大距離、減衰率(+atten)、減衰率2(+atten*頂点までの距離)
	SpotLight( const Vector& pos, const Vector& dir, float out_angle, float in_angle, float range, float atten0, float atten1 );
	virtual ~SpotLight( );

public:
	void setPosition( const Vector& pos );

private:
	Vector _pos;
};

