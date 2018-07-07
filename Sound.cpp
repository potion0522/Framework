#include "Sound.h"
#include "DxLib.h"
#include "Manager.h"
#include <errno.h>
#include <assert.h>

SoundPtr Sound::getTask( ) {
	return std::dynamic_pointer_cast< Sound >( Manager::getInstance( )->getTask( getTag( ) ) );
}

std::string Sound::getTag( ) {
	return "SOUND";
}

Sound::Sound( std::string sound_path ) :
_sound_path( sound_path ){
}

Sound::~Sound( ) {
}

void Sound::initialize( ) {
}

void Sound::finalize( ) {
}

void Sound::update( ) {
}

bool Sound::isPlaying( int handle ) {
	if ( CheckSoundMem( handle ) == TRUE ) {
		return true;
	}
	return false;
}

void Sound::play( int handle, bool loop, bool top, int volume ) {
	checkHandle( handle );

	if ( volume > 0 ) {
		ChangeVolumeSoundMem( volume, handle );
	}

	int top_flag = FALSE;
	if ( top ) {
		top_flag = TRUE;
	}
	if ( !loop ) {
		PlaySoundMem( handle, DX_PLAYTYPE_BACK, top_flag );
	} else {
		PlaySoundMem( handle, DX_PLAYTYPE_LOOP, top_flag );
	}

}

void Sound::stop( int handle ) {
	StopSoundMem( handle );
}

void Sound::checkHandle( int handle ) {
	errno_t not_find_handle = handle;
	assert( not_find_handle != -1 );
}

int Sound::load( std::string file_name ) {
	std::string file = _sound_path + "/" + file_name;
	if ( _sound_handles[ file ] == 0 ) {
		_sound_handles[ file ] = LoadSoundMem( file.c_str( ) );
	}
	return _sound_handles[ file ];
}