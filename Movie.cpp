#include "Movie.h"
#include "DxLib.h"

Movie::Movie( ) :
_handle( -1 ) {
}

Movie::~Movie( ) {
	if ( _handle != -1 ) {
		DeleteGraph( _handle );
	}
}

bool Movie::load( const char* path ) {
	_handle = LoadGraph( path );
	return ( _handle != -1 );
}

void Movie::replay( ) {
	SeekMovieToGraph( _handle, 0 );
	play( );
}

void Movie::play( ) {
	PlayMovieToGraph( _handle );
}

void Movie::pause( ) {
	PauseMovieToGraph( _handle );
}

void Movie::draw( float x, float y, bool trans ) const {
	DrawGraphF( x, y, _handle, ( trans ? TRUE : FALSE ) );
}

void Movie::setVolume( int volume ) {
	ChangeMovieVolumeToGraph( volume, _handle );
}

int Movie::getNowPlayingMilliTime( ) const {
	return TellMovieToGraph( _handle );
}

bool Movie::isPlaying( ) const {
	return ( GetMovieStateToGraph( _handle ) == 1 );
}

int Movie::getHandle( ) const {
	return _handle;
}