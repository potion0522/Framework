#include "DxLib.h"
#include "Manager.h"
/*******************************************

�K���ŏ��ɌĂ΂��֐�
�v���W�F�N�g���� 
int WINAPI WinMain ..... 
�������̂��ȗ��ł���

*******************************************/

extern int main( );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Manager* manager = Manager::getInstance( );
	main( );
	manager->startGame( );
	manager->finalize( );
	return 0;
}