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
#include "Movie.h"
#include "Model.h"
#include "Screen.h"

#include <string>

PTR( Test );

const double SCREEN_WIDTH = 1280;
const double SCREEN_HEIGHT = 720;

class Test : public Task {
public:
	static TestPtr getTask( ) { return std::dynamic_pointer_cast< Test >( Manager::getInstance( )->getTask( getTag( ) ) ); }
	static std::string getTag( ) { return "TEST"; }

public:
	Test( ) { }
	~Test( ) { }

public:
	void initialize( ) {
		_screen = ScreenPtr( new Screen( 1280, 720 ) );

		_movie = MoviePtr( new Movie );
		_movie->load( "TutorialMovie.avi" );
		_movie->play( );

		_model = ModelPtr( new Model );
		_model->alloc( 2 );
		Vector pos[ 4 ] = {
			Vector( -0.5,  0.5, 0 ),
			Vector(  0.5,  0.5, 0 ),
			Vector( -0.5, -0.5, 0 ),
			Vector(  0.5, -0.5, 0 ),
		};
		Model::Vertex vert[ 4 ] = {
			Model::Vertex( pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ),
			Model::Vertex( pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ),
			Model::Vertex( pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ),
			Model::Vertex( pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ),
		};
		_model->setVertex( 0, vert[ 0 ] );
		_model->setVertex( 1, vert[ 1 ] );
		_model->setVertex( 2, vert[ 2 ] );

		_model->setVertex( 3, vert[ 1 ] );
		_model->setVertex( 4, vert[ 3 ] );
		_model->setVertex( 5, vert[ 2 ] );

		_model->setTexture( _screen );
	}

	void update( ) {
		if ( _movie->getNowPlayingMilliTime( ) > 10000 ) {
			_movie->replay( );
		}

		{
			Screen::Scope scope = _screen->createScope( );
			_screen->setDrawScreen( scope );
			_movie->draw( 0, 0, false );
		}

		CameraPtr camera = Camera::getTask( );
		camera->setCameraUp( Vector( 0, 1, 0 ) );
		camera->setCamera( Vector( 0, 0, -1 ), Vector( 0, 0, 0 ) );
		camera->setNearFar( 0.1f, 500.0f );

		_model->draw( );

		DrawerPtr drawer = Drawer::getTask( );
		drawer->flip( );

	}

private:
	ModelPtr _model;
	MoviePtr _movie;
	ScreenPtr _screen;
};


int main( ) {
	Manager* manager = Manager::getInstance( );
	manager->setScreenSize( ( int )SCREEN_WIDTH, ( int )SCREEN_HEIGHT );
	//manager->setUseZBaffur( true );
	//manager->setWriteZBaffur( true );
	//manager->setUseLighting( true );
	//manager->setUseLightTypeDir( true, 0, -1, 0 );

	manager->add( Drawer::getTag( )  , TaskPtr( new Drawer( "." ) ) );
	manager->add( Keyboard::getTag( ), TaskPtr( new Keyboard ) );
	manager->add( Mouse::getTag( )   , TaskPtr( new Mouse ) );
	manager->add( Camera::getTag( )  , TaskPtr( new Camera ) );
	manager->add( Test::getTag( )    , TaskPtr( new Test ) );

	return 0;
}