#pragma once
#include "smart_ptr.h"

PTR( Movie );

class Movie {
public:
	Movie( );
	virtual ~Movie( );

public:
	bool load( const char* path );
	void replay( );
	void play( );
	void pause( );
	void draw( float x, float y, bool trans ) const;
	// 0`255
	void setVolume( int volume );
	int getNowPlayingMilliTime( ) const;
	// Ä¶I—¹‚ÍŒŸ’m‚µ‚È‚¢
	bool isPlaying( ) const;
	int getHandle( ) const;

private:
	int _handle;
};

