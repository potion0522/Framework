#pragma once

class Event {
public:
	Event( ) { };
	virtual ~Event( ) { };

public:
	virtual void onEvent( ) = 0;
};

