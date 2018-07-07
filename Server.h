#pragma once
#include "Base.h"
#include <string>

PTR( Server );

class Server : public Base {
public:
	static ServerPtr getTask( );
	static std::string getTag( );

public:
	Server( );
	virtual ~Server( );

public:
	void initialize( );
	void finalize( );
	void update( );
};

