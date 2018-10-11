#pragma once

class Event {
public:
	Event( ) { };
	virtual ~Event( ) { };

public:
	virtual void activate( ) = 0;
};

