#include "Manager.h"
#include "smart_ptr.h"
#include "Drawer.h"
#include "Vector.h"
#include "Mouse.h"

#include <string>

PTR( Test );

class Test : public Base {
	// Base
public:
	static TestPtr getTask( ) {
		return std::dynamic_pointer_cast< Test >( Manager::getInstance( )->getTask( getTag( ) ) );
	}

	static std::string getTag( ) { 
		return "TEST";
	}


	// constructor & destructor
public:
	Test( ) {
	}
	~Test( ) {
	}


	// function
public:
	void initialize( ) {
	}

	void update( ) {
		// 1辺の長さ
		const int SQUARE_SIZE = 100;
		const int MAX_VERTEX = 4;

		// 四角の中心
		const Vector BASE_POS = Vector( 100, 100 );

		// 四隅
		int half_size = SQUARE_SIZE / 2;
		Vector points[ MAX_VERTEX ] = {
			Vector( -half_size, -half_size ) + BASE_POS, // 左上
			Vector( -half_size,  half_size ) + BASE_POS, // 左下
			Vector(  half_size,  half_size ) + BASE_POS, // 右下
			Vector(  half_size, -half_size ) + BASE_POS, // 右上
		};

		// マウス座標取得
		Vector mouse_pos = Mouse::getTask( )->getPoint( );

		// 内側にあるかどうかを格納する bool
		bool in_side = true;

		// 内外判定
		for ( int i = 0; i < MAX_VERTEX; i++ ) {
			int idx1 = i;
			int idx2 = ( i + 1 ) % MAX_VERTEX;

			Vector vertex_a = points[ idx1 ];
			Vector vertex_b = points[ idx2 ];

			Vector a = vertex_b - vertex_a;
			Vector b = mouse_pos - vertex_b;

			if ( a.x * b.y - b.x * a.y > 0 ) {
				in_side = false;
				break;
			}
		}

		// 内側にあったら文字を表示
		DrawerPtr drawer = Drawer::getTask( );
		if ( in_side ) {
			drawer->drawString( 20, 20, "!! HIT !!", 0xff0000 );
		}

		// 四角を描画
		for ( int i = 0; i < MAX_VERTEX; i++ ) {
			int idx1 = i;
			int idx2 = ( i + 1 ) % MAX_VERTEX;

			Vector vertex_a = points[ idx1 ];
			Vector vertex_b = points[ idx2 ];

			drawer->drawLine( 
				( float )vertex_a.x, ( float )vertex_a.y, 
				( float )vertex_b.x, ( float )vertex_b.y, 
				0xffffff );
		}

		drawer->flip( );
	}


	// value
private:
};


int main( ) {
	Manager* manager = Manager::getInstance( );
	manager->add( Drawer::getTag( ), BasePtr( new Drawer( "." ) ) );
	manager->add( Mouse::getTag( ), BasePtr( new Mouse ) );
	manager->add( Test::getTag( ), BasePtr( new Test ) );

	return 0;
}