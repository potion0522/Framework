#include "Client.h"
#include "Manager.h"
#include "Data.h"
#include "DxLib.h"

const int TCP_PORT = 9850;
const int UDP_PORT = 9900;

const char IP_FILE[ ] = "ip.ini";

const char PHASE_READY_STRING[ ] = "READY";
const char PHASE_CONNECTING_STRING[ ] = "CONNECTING";

ClientPtr Client::getTask( ) {
	return std::dynamic_pointer_cast< Client >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Client::Client( DataPtr recvdata_tcp, DataPtr recvdata_udp ) :
_recvdata_tcp( recvdata_tcp ),
_recvdata_udp( recvdata_udp ),
_phase( Client::PHASE_READY ),
_server_ip( IP( ) ),
_handle( -1 ),
_recieving_tcp( false ) {
	readIP( );
}

Client::~Client( ) {
}

void Client::finalize( ) {
}

void Client::initialize( ) {
}

void Client::update( ) {
	switch ( _phase ) {
	case Client::PHASE_READY:
		connect( );
		break;

	case Client::PHASE_CONNECTING:
		lost( );
		recv( );
		break;

	default:
		break;
	}
}

void Client::readIP( ) {
	int handle = 0;
	std::string path = IP_FILE;

	handle = FileRead_open( path.c_str( ) );
	if ( handle == 0 ) {
		handle = FileRead_open( ( "../" + path ).c_str( ) );
	}

	FileRead_read( &_server_ip, sizeof( IP ), handle );
	FileRead_close( handle );
}

void Client::connect( ) {
	if ( _handle != -1 ) {
		return;
	}

	IPDATA ip = IPDATA( );
	ip.d1 = _server_ip.d1;
	ip.d2 = _server_ip.d2;
	ip.d3 = _server_ip.d3;
	ip.d4 = _server_ip.d4;

	int handle = ConnectNetWork( ip, TCP_PORT );

	if ( handle == -1 ) {
		return;
	}

	_handle = handle;
	_phase = PHASE_CONNECTING;
}

void Client::lost( ) {
	int handle = GetLostNetWork( );
	if ( handle == -1 ) {
		return;
	}
	if ( handle != _handle ) {
		return;
	}
	CloseNetWork( _handle );
	_phase = PHASE_READY;
	_handle = -1;
}

void Client::recv( ) {
	recvTcp( );
	recvUdp( );
}

void Client::recvTcp( ) {
	_recieving_tcp = false;
	if ( _handle == -1 ) {
		return;
	}

	int result = NetWorkRecv( _handle, _recvdata_tcp->getPtr( ), _recvdata_tcp->getSize( ) );

	if ( result == 0 ) {
		_recieving_tcp = true;
	}
}

void Client::recvUdp( ) {
}

std::string Client::getPhase( ) const {
	std::string phase;
	switch ( _phase ) {
	case Client::PHASE_READY:
		phase = PHASE_READY_STRING;
		break;

	case Client::PHASE_CONNECTING:
		phase = PHASE_CONNECTING_STRING;
		break;

	default:
		break;
	}
	return phase;
}

bool Client::isRecievingTcp( ) const {
	return _recieving_tcp;
}