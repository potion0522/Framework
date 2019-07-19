#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Mathematics.h"

#include <array>
#include <string>

/***************************************************************

	シャドウマップの管理を行う
	マップはこのクラスだけが保持し、
	書き込み開始・終了を外部から呼べるようにする

****************************************************************/

PTR( ShadowDrawer );

class ShadowDrawer : public Task {
public:
	enum MAP_TYPE {
		MAP_TYPE_DYNAMIC_OBJ,
		MAP_TYPE_STATIC_OBJ,
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
	void initialize( ) override;
	void update( ) override;

public:
	void setLightDir( MAP_TYPE type, const Vector& dir );
	void setDrawArea( MAP_TYPE type, const Vector& min, const Vector& max );
	void setUpDrawShadowMap( MAP_TYPE type );
	void endDrawShadowMap( );
	void useShadowMap( MAP_TYPE type );
	void endUseShadowMap( );

private:
	void setUseType( MAP_TYPE type );
	void assertSetUpDrawShadowMap( );
	void assertUseShadowMap( );

private:
	bool _set_up_draw_shadow_map;
	bool _use_shadow_map;
	MAP_TYPE _last_use_type;
	std::array< int, MAX_MAP_TYPE > _handles;
};

