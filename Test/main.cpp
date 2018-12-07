#include "Manager.h"
#include "smart_ptr.h"
#include "Drawer.h"
#include "Vector.h"
#include "Mouse.h"

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
	}

	void update( ) {
		MousePtr mouse = Mouse::getTask( );

		int click_right = mouse->getClickingRight( );
		int click_left = mouse->getClickingLeft( );
		bool down_right = mouse->isClickDownRight( );
		bool down_left = mouse->isClickDownLeft( );
		bool up_right = mouse->isClickUpRight( );
		bool up_left = mouse->isClickUpLeft( );

		static int down_right_cnt = 0;
		static int down_left_cnt = 0;
		static int up_right_cnt = 0;
		static int up_left_cnt = 0;

		down_right_cnt += ( down_right ? 1 : 0 );
		down_left_cnt += ( down_left ? 1 : 0 );
		up_right_cnt += ( up_right ? 1 : 0 );
		up_left_cnt += ( up_left ? 1 : 0 );

		DrawerPtr drawer = Drawer::getTask( );
		const unsigned int WHITE = 0xffffff;
		drawer->drawFormatString( 20, 20, WHITE, "click_right : %d", click_right );
		drawer->drawFormatString( 20, 40, WHITE, "click_left : %d", click_left );
		drawer->drawFormatString( 20, 60, WHITE, "down_right : %d", down_right_cnt );
		drawer->drawFormatString( 20, 80, WHITE, "down_left : %d", down_left_cnt );
		drawer->drawFormatString( 20, 100, WHITE, "up_right : %d", up_right_cnt );
		drawer->drawFormatString( 20, 120, WHITE, "up_left : %d", up_left_cnt );

		drawer->flip( );
	}

private:
};


int main( ) {
	Manager* manager = Manager::getInstance( );
	manager->add( Drawer::getTag( ), BasePtr( new Drawer( "." ) ) );
	manager->add( Mouse::getTag( ), BasePtr( new Mouse ) );
	manager->add( Test::getTag( ), BasePtr( new Test ) );

	return 0;
}