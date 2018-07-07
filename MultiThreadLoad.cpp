#pragma once
#include "MultiThreadLoad.h"
#include "DxLib.h"

const short int STRING_SIZE = 50;

MultiThreadLoad::MultiThreadLoad( std::string message ) :
_message( message ) {
	_flag = true;
	_max = 0;
	_cnt = 0;

	_font_handle = CreateFontToHandle( "メイリオ", STRING_SIZE, -1, DX_FONTTYPE_NORMAL );
	SetUseASyncLoadFlag( TRUE );
}

MultiThreadLoad::MultiThreadLoad( ) {
	_flag = false;
	_max = 0;
	_cnt = 0;
}

MultiThreadLoad::~MultiThreadLoad( ) {
}

void MultiThreadLoad::update( ) {
	while ( _flag ) {

		ProcessMessage( );
		ClearDrawScreen( );

		int temp = GetASyncLoadNum( );
		float length = ( _max - GetASyncLoadNum( ) ) / _max;

		if ( length < 1 ) {
		}

		//ロードし終わったら
		if ( length == 1 ) {
			////終了////
			SetUseASyncLoadFlag( FALSE );
			return;
		}
		ScreenFlip( );
		WaitVSync( 1 );
	}
}

void MultiThreadLoad::setMaxLength( float max ) {
	_max = max;
}