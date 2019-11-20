#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Mathematics.h"

#include <array>
#include <string>

/***************************************************************

	�V���h�E�}�b�v�̊Ǘ����s��
	�}�b�v�͂��̃N���X�������ێ����A
	�������݊J�n�E�I�����O������Ăׂ�悤�ɂ���

****************************************************************/

PTR( ShadowDrawer );

class ShadowDrawer : public Task {
public:
	enum MAP_TYPE {
		MAP_1,
		MAP_2,
		MAP_TYPE_NONE,
		MAX_MAP_TYPE
	};

public:
	static ShadowDrawerPtr getTask( );
	static std::string getTag( ) { return "SHADOW_DRAWER"; }

public:
	ShadowDrawer( const Vector& handle1_size, const Vector& handle2_size = Vector( 1024, 1024 ) );
	virtual ~ShadowDrawer( );

public:
	virtual void initialize( ) override;
	virtual void update( ) override;

public:
	void setLightDir( MAP_TYPE type, const Vector& dir );
	void setDrawArea( MAP_TYPE type, const Vector& min, const Vector& max );
	void setupDrawShadowMap( MAP_TYPE type );
	void endDrawShadowMap( );
	void useShadowMap( );
	void endUseShadowMap( );
	void clearShadow( );

private:
	void assertSetupDrawShadowMap( );
	void assertUseShadowMap( );

private:
	bool _set_up_draw_shadow_map;
	bool _use_shadow_map;
	MAP_TYPE _last_use_type;
	std::array< int, MAX_MAP_TYPE > _handles;
};

