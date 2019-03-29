#pragma once
#include "Light.h"
#include "smart_ptr.h"

PTR( SpotLight );

class SpotLight : public Light {
public:
	// �ʒu�A�p�x�A���C�g�̉e���p�x(0~PI)�A���C�g�̌����J�n�p�x(0~out_angle)�A�e���ő勗���A������(+atten)�A������2(+atten*���_�܂ł̋���)
	SpotLight( const Vector& pos, const Vector& dir, float out_angle, float in_angle, float range, float atten0, float atten1 );
	virtual ~SpotLight( );

public:
	void setPosition( const Vector& pos );

private:
	Vector _pos;
};

