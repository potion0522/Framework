#include "ShadowDrawer.h"
#include "Manager.h"
#include <assert.h>

#include "DxLib.h"

ShadowDrawerPtr ShadowDrawer::getTask( ) {
	return std::dynamic_pointer_cast< ShadowDrawer >( Manager::getInstance( )->getTask( getTag( ) ) );
}

ShadowDrawer::ShadowDrawer( const Vector& dynamic_obj_map_size, const Vector& static_obj_map_size ) :
_last_use_type( MAP_TYPE_NONE ),
_set_up_draw_shadow_map( false ),
_use_shadow_map( false ) {
	_handles[ MAP_1 ] = MakeShadowMap( ( int )dynamic_obj_map_size.x, ( int )dynamic_obj_map_size.y );
	_handles[ MAP_2 ] = MakeShadowMap( ( int )static_obj_map_size.x , ( int )static_obj_map_size.y );
	setLightDir( MAP_1, Vector( 0, -1, 0 ) );
	setLightDir( MAP_2 , Vector( 0, -1, 0 ) );
}

ShadowDrawer::~ShadowDrawer( ) {
	for ( int i = 0; i < MAX_MAP_TYPE; i++ ) {
		DeleteShadowMap( _handles[ i ] );
	}
}

void ShadowDrawer::initialize( ) {
}

void ShadowDrawer::update( ) {
#ifdef _DEBUG
	assertSetupDrawShadowMap( );
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

void ShadowDrawer::setupDrawShadowMap( MAP_TYPE type ) {
#ifdef _DEBUG
	assertSetupDrawShadowMap( );
	assertUseShadowMap( );
#endif
	ShadowMap_DrawSetup( _handles[ type ] );
	_last_use_type = type;
	_set_up_draw_shadow_map = true;
}

void ShadowDrawer::endDrawShadowMap( ) {
	ShadowMap_DrawEnd( );
	_last_use_type = MAP_TYPE_NONE;
	_set_up_draw_shadow_map = false;
}

void ShadowDrawer::useShadowMap( ) {
#ifdef _DEBUG
	assertSetupDrawShadowMap( );
#endif
	for ( int i = 0; i < MAX_MAP_TYPE; i++ ) {
		if ( _handles[ i ] == -1 ) {
			continue;
		}
		SetUseShadowMap( i, _handles[ i ] );
	}
	_use_shadow_map = true;
}

void ShadowDrawer::endUseShadowMap( ) {
	for ( int i = 0; i < MAX_MAP_TYPE; i++ ) {
		SetUseShadowMap( i, -1 );
	}
	_use_shadow_map = false;
}

void ShadowDrawer::clearShadow( ) {
	for ( int i = 0; i < MAX_MAP_TYPE; i++ ) {
		setupDrawShadowMap( ( MAP_TYPE )i );
		endDrawShadowMap( );
	}
}

void ShadowDrawer::assertSetupDrawShadowMap( ) {
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