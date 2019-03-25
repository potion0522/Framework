#include "Speaker.h"
#include "DxLib.h"

Speaker::Speaker( int handle ) :
_handle( handle ),
_loop( false ) {
}

Speaker::~Speaker( ) {
	DeleteSoundMem( _handle );
}

void Speaker::play( ) {
	int play_type = ( _loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK );
	int play_top  = ( _play_top ? FALSE : TRUE );

	PlaySoundMem( _handle, play_type, play_top );
}

void Speaker::pause( ) {
	_play_top = false;
	StopSoundMem( _handle );
}

void Speaker::stop( ) {
	_play_top = true;
	StopSoundMem( _handle );
}

void Speaker::setVolume( float ratio ) {
	const int MAX_VOL = 255;
	ChangeVolumeSoundMem( ( int )( MAX_VOL * ratio ), _handle );
}

void Speaker::setLoop( bool loop ) {
	_loop = loop;
}

bool Speaker::isPlaying( ) const {
	return ( CheckSoundMem( _handle ) == 1 );
}