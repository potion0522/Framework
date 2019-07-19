#include "Manager.h"
#include "smart_ptr.h"
#include "Drawer.h"
#include "Model.h"
#include "Mouse.h"
#include "Camera.h"
#include "Sound.h"
#include "Speaker.h"
#include "Mathematics.h"
#include "Keyboard.h"

#include "DxLib.h"

#include <string>

PTR( Test );

class Test : public Task {
public:
	static TestPtr getTask( ) { return std::dynamic_pointer_cast< Test >( Manager::getInstance( )->getTask( getTag( ) ) ); }
	static std::string getTag( ) { return "TEST"; }

public:
	Test( ) { }
	~Test( ) { }

public:
	void initialize( ) {
		CameraPtr camera = Camera::getTask( );
		camera->setCameraUp( Vector( 0, 1, 0 ) );
		camera->setCamera( Vector( 2, 2, -1 ), Vector( ) );

		{
			_floor = ModelPtr( new Model );
			_floor->alloc( 2 );

			Vector vert_pos[ 4 ] = {
				Vector( -1000, 0,  1000 ) * 0.001,
				Vector(  1000, 0,  1000 ) * 0.001,
				Vector( -1000, 0, -1000 ) * 0.001,
				Vector(  1000, 0, -1000 ) * 0.001,
			};
			Model::Vertex vert[ 4 ] = {
				Model::Vertex( vert_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ),
				Model::Vertex( vert_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ),
				Model::Vertex( vert_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ),
				Model::Vertex( vert_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ),
			};

			_floor->setVertex( 0, vert[ 0 ] );
			_floor->setVertex( 1, vert[ 1 ] );
			_floor->setVertex( 2, vert[ 2 ] );

			_floor->setVertex( 3, vert[ 1 ] );
			_floor->setVertex( 4, vert[ 3 ] );
			_floor->setVertex( 5, vert[ 2 ] );

			_floor->setTexture( Drawer::getTask( )->getImage( "texture.png" ) );
		}

		{
			_obj = ModelPtr( new Model );
			_obj->alloc( 2 );

			Vector vert_pos[ 4 ] = {
				( Vector( -250,  250, 0 ) ) * 0.001,
				( Vector(  250,  250, 0 ) ) * 0.001,
				( Vector( -250, -250, 0 ) ) * 0.001,
				( Vector(  250, -250, 0 ) ) * 0.001,
			};
			Model::Vertex vert[ 4 ] = {
				Model::Vertex( vert_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ),
				Model::Vertex( vert_pos[ 1 ], 1.0f / 3, 0, Vector( 0, 1, 0 ) ),
				Model::Vertex( vert_pos[ 2 ], 0, 1.0f / 4, Vector( 0, 1, 0 ) ),
				Model::Vertex( vert_pos[ 3 ], 1.0f / 3, 1.0f / 4, Vector( 0, 1, 0 ) ),
			};

			_obj->setVertex( 0, vert[ 0 ] );
			_obj->setVertex( 1, vert[ 1 ] );
			_obj->setVertex( 2, vert[ 2 ] );

			_obj->setVertex( 3, vert[ 1 ] );
			_obj->setVertex( 4, vert[ 3 ] );
			_obj->setVertex( 5, vert[ 2 ] );

			_obj->setTexture( Drawer::getTask( )->getImage( "hone.png" ) );
		}

		_shadow_map_handle = MakeShadowMap( 512, 512 );
		_shadow_map_handle_tmp = MakeShadowMap( 512, 512 );
		SetShadowMapLightDirection( _shadow_map_handle, VGet( 0, -1, 1 ) );
		SetShadowMapLightDirection( _shadow_map_handle_tmp, VGet( 0, -1, 1 ) );
		SetShadowMapDrawArea( _shadow_map_handle, VGet( -1, -1, -1 ), VGet( 1, 1, 1 ) );
		SetShadowMapDrawArea( _shadow_map_handle_tmp, VGet( -1, -1, -1 ), VGet( 1, 1, 1 ) );
	}

	void update( ) {
		static int cnt = 0;
		cnt++;
		Vector pos = Vector( 1000 - cnt, 250, -0 ) * 0.001;


		ShadowMap_DrawSetup( _shadow_map_handle );
		_obj->draw( pos );
		ShadowMap_DrawEnd( );

		DrawerPtr drawer = Drawer::getTask( );
		ShadowMap_DrawSetup( _shadow_map_handle_tmp );
		drawer->drawSphere( Vector( ), 0.1f, 50, 0xff0000, true );
		ShadowMap_DrawEnd( );

		_obj->draw( pos );

		SetUseShadowMap( 0, _shadow_map_handle );
		_floor->draw( );
		SetUseShadowMap( 0, -1 );
		SetUseShadowMap( 0, _shadow_map_handle_tmp );
		_floor->draw( );
		SetUseShadowMap( 0, -1 );

		drawer->flip( );
	}

private:
	ModelPtr _obj;
	ModelPtr _floor;
	int _shadow_map_handle;
	int _shadow_map_handle_tmp;
};


int main( ) {
	Manager* manager = Manager::getInstance( );
	manager->setScreenSize( 1280, 720 );
	manager->setUseZBaffur( true );
	manager->setWriteZBaffur( true );
	manager->setUseLighting( true );
	manager->setUseLightTypeDir( true, 0, -1, 0 );

	manager->add( Drawer::getTag( )  , TaskPtr( new Drawer( "." ) ) );
	manager->add( Keyboard::getTag( ), TaskPtr( new Keyboard ) );
	manager->add( Mouse::getTag( )   , TaskPtr( new Mouse ) );
	manager->add( Camera::getTag( )  , TaskPtr( new Camera ) );
	manager->add( Test::getTag( )    , TaskPtr( new Test ) );
	manager->add( Sound::getTag( )   , TaskPtr( new Sound( "." ) ) );

	return 0;
}