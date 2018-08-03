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
_connect_flag( false ),
_handle_tcp( -1 ),
_handle_udp( -1 ),
_recieving_tcp( false ),
_recieving_udp( false ) {
}

Client::~Client( ) {
}

void Client::finalize( ) {
	disConnect( );
}

void Client::initialize( ) {
	_phase = Client::PHASE_READY;
	_server_ip = IP( );
	_recieving_tcp = false;
	_recieving_udp = false;

	_handle_udp = MakeUDPSocket( UDP_PORT );
	readIP( );
}

void Client::update( ) {
	if ( !_connect_flag ) {
		return;
	}

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

void Client::disConnect( ) {
	CloseNetWork( _handle_tcp );
	_handle_tcp = -1;

	DeleteUDPSocket( _handle_udp );
	_handle_udp = -1;
}

void Client::sendTcp( DataPtr data ) {
	int result = -1;
	result = NetWorkSend( _handle_tcp, data->getPtr( ), data->getSize( ) );
}

void Client::setConnectFlag( bool connect ) {
	_connect_flag = connect;

	if ( !_connect_flag ) {
		disConnect( );
		initialize( );
	}
}

void Client::readIP( std::string ip ) {
	const int MAX_IDX = 4;
	unsigned char num[ MAX_IDX ] = { };
	for ( int i = 0; i < MAX_IDX; i++ ) {
		size_t pos = ip.find_first_of( '.' );
		if ( pos == std::string::npos && i != MAX_IDX - 1 ) {
			break;
		}
		num[ i ] = std::atoi( ip.substr( 0, pos ).c_str( ) );
		ip = ip.substr( pos + 1, ip.length( ) - pos - 1 );
	}
	_server_ip.d1 = num[ 0 ];
	_server_ip.d2 = num[ 1 ];
	_server_ip.d3 = num[ 2 ];
	_server_ip.d4 = num[ 3 ];
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
	if ( _handle_tcp != -1 ) {
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

	_handle_tcp = handle;
	_phase = PHASE_CONNECTING;
}

void Client::lost( ) {
	int handle = GetLostNetWork( );
	if ( handle == -1 ) {
		return;
	}
	if ( handle != _handle_tcp ) {
		return;
	}
	CloseNetWork( _handle_tcp );
	_phase = PHASE_READY;
	_handle_tcp = -1;
}

void Client::recv( ) {
	recvTcp( );
	recvUdp( );
}

void Client::recvTcp( ) {
	_recieving_tcp = false;
	if ( _handle_tcp == -1 ) {
		return;
	}
	if ( GetNetWorkDataLength( _handle_tcp ) < 1 ) {
		return;
	}

	int result = NetWorkRecv( _handle_tcp, _recvdata_tcp->getPtr( ), _recvdata_tcp->getSize( ) );
	if ( result == 0 ) {
		_recieving_tcp = true;
	}
}

void Client::recvUdp( ) {
	_recieving_udp = false;

	if ( CheckNetWorkRecvUDP( _handle_udp ) != TRUE ) {
		return;
	}

	int result = NetWorkRecvUDP( _handle_udp, NULL, NULL, _recvdata_udp->getPtr( ), _recvdata_udp->getSize( ), FALSE );
	if ( result >= 0 ) {
		_recieving_udp = true;
	}
}

std::string Client::getServerIP( ) const {
	std::string ip;
	ip += std::to_string( _server_ip.d1 );
	ip += ".";
	ip += std::to_string( _server_ip.d2 );
	ip += ".";
	ip += std::to_string( _server_ip.d3 );
	ip += ".";
	ip += std::to_string( _server_ip.d4 );

	return ip;
}

std::string Client::getClientIP( ) const {
	IPDATA ip = IPDATA( );
	GetMyIPAddress( &ip );

	std::string ip_str;
	ip_str += std::to_string( ip.d1 );
	ip_str += ".";
	ip_str += std::to_string( ip.d2 );
	ip_str += ".";
	ip_str += std::to_string( ip.d3 );
	ip_str += ".";
	ip_str += std::to_string( ip.d4 );

	return ip_str;
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

bool Client::isRecievingUdp( ) const {
	return _recieving_udp;
}