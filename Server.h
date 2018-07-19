#pragma once
#include "Base.h"
#include <string>

PTR( Server );
PTR( Data );

class Server : public Base {
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
	int sendTcp( DataPtr data );

private:
	void accept( );
	void lost( );
	void recv( );
	void recvTcp( );

public:
	bool isRecievingTcp( ) const;
	std::string getServerIP( ) const;
	std::string getClientIP( ) const;

private:
	int _handle;
	bool _recieving_tcp;

	DataPtr _recvdata_tcp;
};

