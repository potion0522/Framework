#include "Manager.h"
#include "smart_ptr.h"
#include "Drawer.h"
#include "Model.h"
#include "Mouse.h"
#include "Camera.h"
#include "Mathematics.h"

#include <string>

PTR( Test );

class Test : public Base {
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
		camera->setCamera( Vector( 0, 0, -3 ), Vector( ) );

		// model
		const int DIV_NUM = 50;
		_model = ModelPtr( new Model );
		_model->alloc( DIV_NUM * DIV_NUM * 4 );
		_model->setTexture( Drawer::getTask( )->getImage( "Test/texture.png" ) );

		// èc
		for ( int i = 0; i < DIV_NUM; i++ ) {
			Vector r1 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / DIV_NUM * ( ( i + 0 ) % DIV_NUM ) ).multiply( Vector( 0, 1000.0, 0 ) );
			Vector r2 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / DIV_NUM * ( ( i + 1 ) % DIV_NUM ) ).multiply( Vector( 0, 1000.0, 0 ) );

			// â°
			for ( int j = 0; j < DIV_NUM * 2; j++ ) {
				Matrix rot1 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / DIV_NUM * 2 * ( ( j + 0 ) % ( DIV_NUM * 2 ) ) );
				Matrix rot2 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / DIV_NUM * 2 * ( ( j + 1 ) % ( DIV_NUM * 2 ) ) );

				Vector ver_pos[ 4 ] = {
					rot1.multiply( r1 ) * 0.001, // ç∂è„
					rot2.multiply( r1 ) * 0.001, // âEè„
					rot1.multiply( r2 ) * 0.001, // ç∂â∫
					rot2.multiply( r2 ) * 0.001, // âEâ∫
				};

				Model::Vertex ver[ 4 ] = {
					Model::Vertex( ver_pos[ 0 ], 0, 0, ver_pos[ 0 ] ),
					Model::Vertex( ver_pos[ 1 ], 0, 0, ver_pos[ 1 ] ),
					Model::Vertex( ver_pos[ 2 ], 0, 0, ver_pos[ 2 ] ),
					Model::Vertex( ver_pos[ 3 ], 0, 0, ver_pos[ 3 ] ),
				};

				int idx = ( i * DIV_NUM * 2 + j ) * 6;
				_model->setVertex( idx + 0, ver[ 0 ] );
				_model->setVertex( idx + 1, ver[ 1 ] );
				_model->setVertex( idx + 2, ver[ 2 ] );

				_model->setVertex( idx + 3, ver[ 1 ] );
				_model->setVertex( idx + 4, ver[ 3 ] );
				_model->setVertex( idx + 5, ver[ 2 ] );

			}
		}
	}

	void update( ) {
		_model->draw( );

		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawSphere( Vector( ), 10, 100, 0xff0000 );
		drawer->flip( );
	}

private:
	ModelPtr _model;
};


int main( ) {
	Manager* manager = Manager::getInstance( );
	manager->setUseZBaffur( true );
	manager->setWriteZBaffur( true );

	manager->add( Drawer::getTag( ), BasePtr( new Drawer( "." ) ) );
	manager->add( Mouse::getTag( ), BasePtr( new Mouse ) );
	manager->add( Camera::getTag( ), BasePtr( new Camera ) );
	manager->add( Test::getTag( ), BasePtr( new Test ) );

	return 0;
}