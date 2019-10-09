#include "Manager.h"
#include "smart_ptr.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Camera.h"
#include "Mathematics.h"
#include "Keyboard.h"
#include "ModelMV1.h"
#include "DxLib.h"
#include "BezierLine.h"

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
		camera->setCameraUp( Vector( 0, 0, 1 ) );
		camera->setCamera( Vector( 0, 3, 0 ), Vector( ) );
		camera->setNearFar( 0.1f, 500.0f );
	}

	void update( ) {
		const int MAX_TIME = 5000;
		static int time = 0;
		time += Manager::getInstance( )->getDeltaMilliTime( );
		if ( MAX_TIME < time ) {
			time = MAX_TIME ;
		}

		double ratio = ( double )time / MAX_TIME;
		BezierLinePtr bezier( new BezierLine );
		std::vector< Vector > points;
		points.push_back( Vector(    0,    0,     0 ) );
		points.push_back( Vector( 1000, 1000, -1000 ) );
		points.push_back( Vector( 1000, 1000,     0 ) );
		Vector pos = bezier->getPoint( ratio, points );


		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawSphere( pos * 0.001                        , 0.2f, 50, 0xff0000, true );
		drawer->drawSphere( Vector( 0, 0, 0 ) * 0.001          , 0.2f, 50, 0x0000ff, false );
		drawer->drawSphere( Vector( 1000, 1000, -1000 ) * 0.001, 0.2f, 50, 0x0000ff, false );
		drawer->drawSphere( Vector( 1000, 1000, 0 ) * 0.001    , 0.2f, 50, 0x0000ff, false );
		drawer->flip( );
	}

private:
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