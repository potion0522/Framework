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

#include "Book.h"

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
		camera->setCameraUp( Vector( 0, 0, 1 ) );
		camera->setCamera( Vector( 0, 5, 0 ), Vector( ) );
		camera->setNearFar( 0.1f, 500.0f );

		_book = BookPtr( new Book );
	}

	void update( ) {
		static int c = 0;
		c++;
		_book->update( );
		_book->draw( );

		DrawerPtr drawer = Drawer::getTask( );
		Vector size = _book->getSize( );

		drawer->drawFormatString( 20, 20, 0xff0000, "%f,%f,%f", size.x, size.y, size.z );
		drawer->drawSphere( Vector( ), 10.0f, 50, 0xff0000, false );

		drawer->drawSphere( Vector( -size.x, 0,  size.z / 2 ), 0.5f, 50, 0x0000ff, true );
		drawer->drawSphere( Vector(       0, 0,  size.z / 2 ), 0.5f, 50, 0x0000ff, true );
		drawer->drawSphere( Vector( -size.x, 0, -size.z / 2 ), 0.5f, 50, 0x0000ff, true );
		drawer->drawSphere( Vector(       0, 0, -size.z / 2 ), 0.5f, 50, 0x0000ff, true );

		drawer->drawSphere( Vector( -2000, 0,  1500 ) * 0.001, 0.5f, 50, 0xff00ff, true );
		drawer->drawSphere( Vector(     0, 0,  1500 ) * 0.001, 0.5f, 50, 0xff00ff, true );
		drawer->drawSphere( Vector( -2000, 0, -1500 ) * 0.001, 0.5f, 50, 0xff00ff, true );
		drawer->drawSphere( Vector(     0, 0, -1500 ) * 0.001, 0.5f, 50, 0xff00ff, true );

		drawer->flip( );
	}

private:
	BookPtr _book;
};


int main( ) {
	Manager* manager = Manager::getInstance( );
	manager->setScreenSize( 1280, 720 );
	manager->setUseZBaffur( true );
	manager->setWriteZBaffur( true );
	//manager->setUseLighting( true );
	//manager->setUseLightTypeDir( true, 0, -1, 0 );

	manager->add( Drawer::getTag( )  , TaskPtr( new Drawer( "." ) ) );
	manager->add( Keyboard::getTag( ), TaskPtr( new Keyboard ) );
	manager->add( Mouse::getTag( )   , TaskPtr( new Mouse ) );
	manager->add( Camera::getTag( )  , TaskPtr( new Camera ) );
	manager->add( Test::getTag( )    , TaskPtr( new Test ) );

	return 0;
}