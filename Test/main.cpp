#include "Manager.h"
#include "smart_ptr.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Camera.h"
#include "Mathematics.h"
#include "Keyboard.h"
#include "ModelMV1.h"
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
		camera->setCamera( Vector( 0, 1, -3 ), Vector( ) );
		camera->setNearFar( 0.1f, 500.0f );

		_model = ModelMV1Ptr( new ModelMV1 );
		_model->load( "model/old_wooden_table.mv1" );
		_model->setTexture( "texture/owt_bump.png", 0 );
		_model->setScale( Vector( 0.01, 0.01, 0.01 ) );
	}

	void update( ) {
		static int c = 0;
		c++;
		_model->setRotate( Vector( PI2 * 0.01 * c, PI2 * 0.01 * c, PI2 * 0.01 * c ) );
		_model->setPos( Vector( c * 0.001, 0, 0 ) );
		_model->draw( );

		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawSphere( Vector( ), 10.0f, 50, 0xff0000, false );
		drawer->drawSphere( Vector( ), 0.1f, 50, 0x00ff00, true );
		drawer->flip( );
	}

private:
	ModelMV1Ptr _model;
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

	return 0;
}