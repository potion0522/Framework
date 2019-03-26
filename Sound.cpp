#include "Sound.h"
#include "DxLib.h"
#include "Manager.h"
#include "Speaker2D.h"
#include "Speaker3D.h"

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

Speaker2DPtr Sound::loadSound2D( const char* file_path ) const {
	int handle = getHandle( file_path );
	return Speaker2DPtr( new Speaker2D( handle ) );
}

Speaker3DPtr Sound::loadSound3D( const char* file_path ) const {
	SetCreate3DSoundFlag( TRUE ); // 3Dフラグ
	int handle = getHandle( file_path );
	SetCreate3DSoundFlag( FALSE ); // 2Dフラグに戻す

	return Speaker3DPtr( new Speaker3D( handle ) );
}

void Sound::set3DSoundListener( const Vector& pos, const Vector& front_pos ) {
	VECTOR pos_dx       = VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z );
	VECTOR front_pos_dx = VGet( ( float )front_pos.x, ( float )front_pos.y, ( float )front_pos.z );
	Set3DSoundListenerPosAndFrontPos_UpVecY( pos_dx, front_pos_dx );
}

int Sound::getHandle( const char* file_path ) const {
	std::string path;
	path = path + FOLDER_PATH + "/" + file_path;

	const int SOUND_LOAD_ERROR = -1;
	int handle = LoadSoundMem( path.c_str( ) );
	assert( SOUND_LOAD_ERROR != handle );

	return handle;
}
