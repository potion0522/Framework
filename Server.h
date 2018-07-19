#pragma once
#include "Base.h"
#include <string>
#include <array>

PTR( Server );
PTR( Data );

class Server : public Base {
public:
	static const int MAX_MACHINES = 2;

public:
	static ServerPtr getTask( );
	static std::string getTag( ) { return "SERVER"; }

public:
	Server( DataPtr recvdata_tcp );
	virtual ~Server( );

public:
	void initialize( );
	void finalize( );
	void update( );

public:
	void createIP( );
	void sendTcp( DataPtr data );

private:
	void accept( );
	void lost( );
	void recv( );
	void recvTcp( );

public:
	bool isRecievingTcp( ) const;
	std::string getServerIP( ) const;
	std::string getClientIP( int idx ) const;

private:
	std::array< int, MAX_MACHINES > _machines;
	bool _recieving_tcp;

	DataPtr _recvdata_tcp;
};

