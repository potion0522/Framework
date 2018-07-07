#pragma once
#include "Base.h"
#include <string>
#include <unordered_map>

PTR( Sound );

class Sound : public Base {
public:
	static SoundPtr getTask( );
	static std::string getTag( );

public:
	Sound( std::string sound_path );
	virtual ~Sound( );

public:
	void initialize( );
	void finalize( );
	void update( );

public:
	bool isPlaying( int handle );
	void play( int handle, bool loop = false, bool top = false, int volume = -1 );
	void stop( int handle );

public:
	int load( std::string file_name );
	void checkHandle( int handle );

private:
	std::string _sound_path;
	std::unordered_map< std::string, int > _sound_handles;
};