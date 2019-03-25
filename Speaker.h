#pragma once
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

private:
	int _handle;
	bool _play_top;
	bool _loop;
};

