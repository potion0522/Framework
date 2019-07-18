#pragma once
#include "Task.h"
#include "Mathematics.h"
#include <string>
/***************************************************

音のロードを行い、それを単体で扱えるものを返すクラス
2D, 3D 両方に対応し、3Dの場合はListenerの役割もこなす

***************************************************/

PTR( Sound );
PTR( Speaker2D );
PTR( Speaker3D );

class Sound : public Task {
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
	Speaker2DPtr loadSound2D( const char* file_path ) const;
	Speaker3DPtr loadSound3D( const char* file_path ) const;
	void set3DSoundListener( const Vector& pos, const Vector& front_pos );

private:
	int getHandle( const char* file_path ) const;

private:
	const char* FOLDER_PATH;
};