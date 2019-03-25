#include "Sound.h"
#include "DxLib.h"
#include "Manager.h"
#include "Speaker.h"

#include <string>
#include <errno.h>
#include <assert.h>

SoundPtr Sound::getTask( ) {
	return std::dynamic_pointer_cast< Sound >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Sound::Sound( const char* folder_path ) :
FOLDER_PATH( folder_path ) {
}

Sound::~Sound( ) {
}

SpeakerPtr Sound::load( const char* file_path ) const {

	std::string path;
	path = path + FOLDER_PATH + "/" + file_path;

	const int SOUND_LOAD_ERROR = -1;
	int handle = LoadSoundMem( path.c_str( ) );

	assert( SOUND_LOAD_ERROR != handle );

	return SpeakerPtr( new Speaker( handle ) );
}