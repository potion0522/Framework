#pragma once
#include "Light.h"
#include "smart_ptr.h"

PTR( PointLight );

class PointLight : public Light {
public:
	// �ʒu�A�e���ő勗���A������(+atten)�A������2(+atten*���_�܂ł̋���)
	PointLight( const Vector& pos, float range, float atten0, float atten1 );
	virtual ~PointLight( );

public:
	void setPosition( const Vector& pos );

private:
	Vector _pos;
};

