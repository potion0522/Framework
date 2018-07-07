#pragma once

class Data {
public:
	Data( );
	virtual ~Data( );

public:
	virtual int getSize( ) const = 0;
	virtual void *getPtr( ) = 0; 
};

