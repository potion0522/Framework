#pragma once
#include "Mathematics.h"

/*****************************************

�eLight�̌��ƂȂ�N���X

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
	// �ʒu�A�e���ő勗���A������(+atten)�A������2(+atten*���_�܂ł̋���)
	Light( const Vector& pos, float range, float atten0, float atten1 );

	// spot
	// �ʒu�A�p�x�A���C�g�̉e���p�x(0~PI)�A���C�g�̌����J�n�p�x(0~out_angle)�A�e���ő勗���A������(+atten)�A������2(+atten*���_�܂ł̋���)
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

