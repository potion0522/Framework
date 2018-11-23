#include "DxLib.h"
#include "Manager.h"

extern void main( );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Manager* manager = Manager::getInstance( );
	main( );
	manager->startGame( );
	manager->finalize( );
	return 0;
}