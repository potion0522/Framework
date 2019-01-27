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
		_model->setTexture( Drawer::getTask( )->getImage( "texture.png" ) );

		const double BALL_RADIUS = 1;

		for ( int i = 0; i < DIV_NUM; i++ ) {
			// y
			Vector point1 = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), ( ( PI * 2 ) / DIV_NUM ) * ( i + 0 ) ).multiply( Vector( 0, BALL_RADIUS, 0 ) );
			Vector point2 = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), ( ( PI * 2 ) / DIV_NUM ) * ( i + 1 ) ).multiply( Vector( 0, BALL_RADIUS, 0 ) );

			for ( int j = 0; j < DIV_NUM * 2; j++ ) {
				// y+ から原点を見ている視点
				Matrix rot1 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), ( ( PI * 2 ) / ( DIV_NUM * 2 ) ) * ( ( j + 0 ) % ( DIV_NUM * 2 ) ) );
				Matrix rot2 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), ( ( PI * 2 ) / ( DIV_NUM * 2 ) ) * ( ( j + 1 ) % ( DIV_NUM * 2 ) ) );

				Vector ver_pos[ 4 ] = {
					rot1.multiply( point1 ), // 左上
					rot2.multiply( point1 ), // 右上
					rot1.multiply( point2 ), // 左下
					rot2.multiply( point2 ), // 右下
				};

				float u1 = ( float )( j + 0 ) / DIV_NUM;
				float u2 = ( float )( j + 1 ) / DIV_NUM;
				float v1 = ( float )( ( -point1.y + BALL_RADIUS ) / ( BALL_RADIUS * 2 ) );
				float v2 = ( float )( ( -point2.y + BALL_RADIUS ) / ( BALL_RADIUS * 2 ) );

				Model::Vertex vertex[ 4 ] = {
					Model::Vertex( ver_pos[ 0 ], u1, v1, ver_pos[ 0 ] ),
					Model::Vertex( ver_pos[ 1 ], u2, v1, ver_pos[ 1 ] ),
					Model::Vertex( ver_pos[ 2 ], u1, v2, ver_pos[ 2 ] ),
					Model::Vertex( ver_pos[ 3 ], u2, v2, ver_pos[ 3 ] )
				};

				int idx = ( i * DIV_NUM * 2 + j ) * 6;
				_model->setVertex( idx + 0, vertex[ 0 ] );
				_model->setVertex( idx + 1, vertex[ 1 ] );
				_model->setVertex( idx + 2, vertex[ 2 ] );

				_model->setVertex( idx + 3, vertex[ 1 ] );
				_model->setVertex( idx + 4, vertex[ 3 ] );
				_model->setVertex( idx + 5, vertex[ 2 ] );
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
	manager->add( Drawer::getTag( ), BasePtr( new Drawer( "." ) ) );
	manager->add( Mouse::getTag( ), BasePtr( new Mouse ) );
	manager->add( Camera::getTag( ), BasePtr( new Camera ) );
	manager->add( Test::getTag( ), BasePtr( new Test ) );

	return 0;
}