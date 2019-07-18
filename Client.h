#pragma once
#include "Task.h"
#include <string>
/*******************************************

ネットワーク通信のクライアントとなるクラス

*******************************************/

PTR( Client );
PTR( Data );

class Client : public Task {
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

private:
	void disConnect( );

public:
	void readIP( std::string ip );
	void sendTcp( DataPtr data );
	void setConnectFlag( bool connect );

private:
	void readIP( );
	void connect( );
	void lost( );
	void recv( );
	void recvTcp( );
	void recvUdp( );

public:
	std::string getClientIP( ) const;
	std::string getServerIP( ) const;
	std::string getPhase( ) const;
	bool isRecievingTcp( ) const;
	bool isRecievingUdp( ) const;

private:
	struct IP {
		unsigned char d1;
		unsigned char d2;
		unsigned char d3;
		unsigned char d4;
	};

	bool _connect_flag;
	int _handle_tcp;
	int _handle_udp;
	bool _recieving_tcp;
	bool _recieving_udp;

	IP _server_ip;
	PHASE _phase;

	DataPtr _recvdata_tcp;
	DataPtr _recvdata_udp;
};

