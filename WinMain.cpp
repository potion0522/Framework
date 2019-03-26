#include "DxLib.h"
#include "Manager.h"
/*******************************************

必ず最初に呼ばれる関数
プロジェクト毎に 
int WINAPI WinMain ..... 
を書くのを省略できる

*******************************************/

extern int main( );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Manager* manager = Manager::getInstance( );
	main( );
	manager->startGame( );
	manager->finalize( );
	return 0;
}