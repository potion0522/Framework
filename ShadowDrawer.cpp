#include "ShadowDrawer.h"
#include "Manager.h"
#include <assert.h>

#include "DxLib.h"

ShadowDrawerPtr ShadowDrawer::getTask( ) {
	return std::dynamic_pointer_cast< ShadowDrawer >( Manager::getInstance( )->getTask( getTag( ) ) );
}

ShadowDrawer::ShadowDrawer( const Vector& dynamic_obj_map_size, const Vector& static_obj_map_size ) :
_last_use_type( MAP_TYPE_NONE ) {
	_handles[ MAP_TYPE_DYNAMIC_OBJ ] = MakeShadowMap( ( int )dynamic_obj_map_size.x, ( int )dynamic_obj_map_size.y );
	_handles[ MAP_TYPE_STATIC_OBJ  ] = MakeShadowMap( ( int )static_obj_map_size.x , ( int )static_obj_map_size.y );
	setLightDir( MAP_TYPE_DYNAMIC_OBJ, Vector( 0, -1, 0 ) );
	setLightDir( MAP_TYPE_STATIC_OBJ , Vector( 0, -1, 0 ) );
}

ShadowDrawer::~ShadowDrawer( ) {
}

void ShadowDrawer::initialize( ) {
}

void ShadowDrawer::update( ) {
#ifdef _DEBUG
	assertSetUpDrawShadowMap( );
	assertUseShadowMap( );
#endif
}

void ShadowDrawer::setLightDir( MAP_TYPE type, const Vector& dir ) {
	SetShadowMapLightDirection( _handles[ type ], VGet( ( float )dir.x, ( float )dir.y, ( float )dir.z ) );
}

void ShadowDrawer::setDrawArea( MAP_TYPE type, const Vector& min, const Vector& max ) {
	SetShadowMapDrawArea( 
		_handles[ type ],
		VGet( ( float )min.x, ( float )min.y, ( float )min.z ), 
		VGet( ( float )max.x, ( float )max.y, ( float )max.z )
	);
}

void ShadowDrawer::setUpDrawShadowMap( MAP_TYPE type ) {
#ifdef _DEBUG
	assertSetUpDrawShadowMap( );
	assertUseShadowMap( );
#endif

	ShadowMap_DrawSetup( _handles[ type ] );
	setUseType( type );
	_set_up_draw_shadow_map = true;
}

void ShadowDrawer::endDrawShadowMap( ) {
	ShadowMap_DrawEnd( );
	setUseType( MAP_TYPE_NONE );
	_set_up_draw_shadow_map = false;
}

void ShadowDrawer::useShadowMap( MAP_TYPE type ) {
#ifdef _DEBUG
	assertSetUpDrawShadowMap( );
	assertUseShadowMap( );
#endif

	SetUseShadowMap( type, _handles[ type ] );
	setUseType( type );
	_use_shadow_map = true;
}

void ShadowDrawer::endUseShadowMap( ) {
	SetUseShadowMap( _last_use_type, -1 );
	setUseType( MAP_TYPE_NONE );
	_use_shadow_map = false;
}

void ShadowDrawer::setUseType( MAP_TYPE type ) {
	_last_use_type = type;
}

void ShadowDrawer::assertSetUpDrawShadowMap( ) {
	if ( _set_up_draw_shadow_map ) {
		errno_t not_endDrawShadowMap = 0;
		assert( not_endDrawShadowMap );
	}
}

void ShadowDrawer::assertUseShadowMap( ) {
	if ( _use_shadow_map ) {
		errno_t not_endUseShadowMap = 0;
		assert( not_endUseShadowMap );
	}
}