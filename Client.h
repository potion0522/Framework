#pragma once
#include "Base.h"
#include <string>

PTR( Client );
PTR( Data );

class Client : public Base {
private:
	enum PHASE {
		PHASE_READY,
		PHASE_CONNECTING
	};

public:
	static ClientPtr getTask( );
	static std::string getTag( ) { return "CLIENT"; }

public:
	Client( DataPtr recvdata_tcp, DataPtr recvdata_udp );
	virtual ~Client( );

public:
	void finalize( );
	void initialize( );
	void update( );

public:
	void sendTcp( DataPtr data );

private:
	void readIP( );
	void connect( );
	void lost( );
	void recv( );
	void recvTcp( );
	void recvUdp( );

public:
	std::string getPhase( ) const;
	bool isRecievingTcp( ) const;

private:
	struct IP {
		unsigned char d1;
		unsigned char d2;
		unsigned char d3;
		unsigned char d4;
	};

	int _handle;
	bool _recieving_tcp;

	IP _server_ip;
	PHASE _phase;

	DataPtr _recvdata_tcp;
	DataPtr _recvdata_udp;
};

