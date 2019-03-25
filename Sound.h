#pragma once
#include "Base.h"
#include <string>

PTR( Sound );
PTR( Speaker );

class Sound : public Base {
public:
	static SoundPtr getTask( );
	static std::string getTag( ) { return "SOUND"; }

public:
	Sound( const char* folder_path );
	virtual ~Sound( );

public:
	void initialize( ) { };
	void finalize( ) { };
	void update( ) { };

public:
	SpeakerPtr load( const char* file_path ) const;

private:
	const char* FOLDER_PATH;
};