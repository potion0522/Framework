#pragma once
/*******************************************

�T�E���h��炷���߂̃x�[�X�ƂȂ�N���X

*******************************************/

class Speaker {
public:
	Speaker( int handle );
	virtual ~Speaker( );

public:
	void play( );
	void pause( );
	void stop( );
	// 0.0 - 1.0
	void setVolume( float ratio );
	void setLoop( bool loop );
	bool isPlaying( ) const;

protected:
	int _handle;
	bool _play_top;
	bool _loop;
};

