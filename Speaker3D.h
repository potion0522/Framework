#pragma once
#include "Speaker.h"
#include "Mathematics.h"
/*******************************************

3D�T�E���h��炷���߂̃N���X

*******************************************/

class Speaker3D : public Speaker {
public:
	Speaker3D( int handle );
	virtual ~Speaker3D( );

public:
	void setPosition( const Vector& pos );
	void setRange( const float& range );
};

