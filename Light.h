#pragma once
#include "Mathematics.h"

/*****************************************

各Lightの元となるクラス

*****************************************/

class Light {
public:
	enum LIGHT_TYPE {
		LIGHT_TYPE_DIRECTION,
		LIGHT_TYPE_POINT,
		LIGHT_TYPE_SPOT,
	};

protected:
	// directional
	Light( const Vector& dir );

	// point
	// 位置、影響最大距離、減衰率(+atten)、減衰率2(+atten*頂点までの距離)
	Light( const Vector& pos, float range, float atten0, float atten1 );

	// spot
	// 位置、角度、ライトの影響角度(0~PI)、ライトの減衰開始角度(0~out_angle)、影響最大距離、減衰率(+atten)、減衰率2(+atten*頂点までの距離)
	Light( const Vector& pos, const Vector& dir, float out_angle, float in_angle, float range, float atten0, float atten1 );
	virtual ~Light( );

public:
	void setEnable( bool flag );
	bool isEnabled( ) const;
	LIGHT_TYPE getType( ) const;

protected:
	LIGHT_TYPE _type;
	int _handle;
};

