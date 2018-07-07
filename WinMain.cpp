#include "DxLib.h"
#include "Manager.h"
#include "DxSetting.h"

extern void main( );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Manager::initialize( );
	main( );

	ManagerPtr manager = Manager::getInstance( );
	manager->allInitialize( );
	while ( ProcessMessage( ) == 0 ) {

		manager->update( );

		if ( CheckHitKey( KEY_INPUT_ESCAPE ) ) {
			break;
		}
	}

	Manager::finalize( );
	return 0;
}