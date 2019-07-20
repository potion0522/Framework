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
#include "ShadowDrawer.h"

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

		ShadowDrawer::getTask( )->setLightDir( ShadowDrawer::MAP_TYPE_DYNAMIC_OBJ, Vector( 0, -1, 1 ) );
	}

	void update( ) {
		static int cnt = 0;
		cnt++;
		Vector pos = Vector( 1000 - cnt, 250, -0 ) * 0.001;
		ShadowDrawerPtr shadow = ShadowDrawer::getTask( );
		shadow->setDrawArea( ShadowDrawer::MAP_TYPE_DYNAMIC_OBJ, Vector( -1, -1, -1 ), Vector( 1, 1, 1 ) );

		shadow->setUpDrawShadowMap( ShadowDrawer::MAP_TYPE_DYNAMIC_OBJ );
		_obj->draw( pos );
		shadow->endDrawShadowMap( );

		shadow->useShadowMap( ShadowDrawer::MAP_TYPE_DYNAMIC_OBJ );
		_floor->draw( );
		shadow->endUseShadowMap( );
		_obj->draw( pos );


		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawSphere( Vector( ), 0.1f, 50, 0xff0000, true );
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
	manager->add( ShadowDrawer::getTag( )   , TaskPtr( new ShadowDrawer( Vector( 512, 512 ) ) ) );

	return 0;
}