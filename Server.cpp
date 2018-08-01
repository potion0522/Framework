#include "Server.h"
#include "Manager.h"
#include "DxLib.h"
#include "Data.h"

const int TCP_PORT = 9850;
const int UDP_PORT = 9900;

const char IP_FILE[ ] = "ip.ini";

ServerPtr Server::getTask( ) {
	return std::dynamic_pointer_cast< Server >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Server::Server( DataPtr recvdata_tcp ) :
_recvdata_tcp( recvdata_tcp ),
_recieving_idx( -1 ) {
	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		_machines[ i ] = -1;
	}
	_handle_udp = MakeUDPSocket( );
	PreparationListenNetWork( TCP_PORT );
}

Server::~Server( ) {
}

void Server::initialize( ) {
}

void Server::finalize( ) {
	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		CloseNetWork( _machines[ i ] );
	}

	DeleteUDPSocket( _handle_udp );
	StopListenNetWork( );
}

void Server::update( ) {
	accept( );
	lost( );
	recv( );
}

void Server::createIP( ) {
	IPDATA ipdata = IPDATA( );
	GetMyIPAddress( &ipdata );

	FILE *fp;
	fopen_s( &fp, IP_FILE, "wb" );

	fwrite( &ipdata, sizeof( IPDATA ), 1, fp );
	fclose( fp );
}

void Server::sendTcp( DataPtr data ) {
	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		if ( _machines[ i ] != -1 ) {
			NetWorkSend( _machines[ i ], data->getPtr( ), data->getSize( ) );
		}
	}
}

void Server::sendUdp( DataPtr data ) {
	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		IPDATA ip = IPDATA( );
		GetNetWorkIP( _machines[ i ], &ip );
		NetWorkSendUDP( _handle_udp, ip, UDP_PORT, data->getPtr( ), data->getSize( ) );
	}

}

void Server::accept( ) {
	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		if ( _machines[ i ] != -1 ) {
			continue;
		}

		int handle = GetNewAcceptNetWork( );
		if ( handle != -1 ) {
			_machines[ i ] = handle;
			break;
		}
	}
}

void Server::lost( ) {
	int handle = GetLostNetWork( );
	if ( handle == -1 ) {
		return;
	}

	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		if ( handle != _machines[ i ] ) {
			continue;
		}

		CloseNetWork( _machines[ i ] );
		_machines[ i ] = -1;
		break;
	}
}

void Server::recv( ) {
	recvTcp( );
}

void Server::recvTcp( ) {
	_recieving_idx = -1;

	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		int handle = _machines[ i ];
		if ( handle == -1 ) {
			continue;
		}


		if ( GetNetWorkDataLength( handle ) < 1 ) {
			continue;
		}

		int result = NetWorkRecv( handle, _recvdata_tcp->getPtr( ), _recvdata_tcp->getSize( ) );

		if ( result == 0 ) {
			_recieving_idx = i;
			break;
		}
	}
}

int Server::getRecievingIdx( ) const {
	return _recieving_idx;
}

std::string Server::getServerIP( ) const {
	IPDATA ipdata = IPDATA( );
	GetMyIPAddress( &ipdata );

	std::string result;
	result += std::to_string( ipdata.d1 );
	result += ".";
	result += std::to_string( ipdata.d2 );
	result += ".";
	result += std::to_string( ipdata.d3 );
	result += ".";
	result += std::to_string( ipdata.d4 );

	return result;
}

std::string Server::getClientIP( int idx ) const {
	std::string result;

	if ( _machines[ idx ] != -1 ) {
		IPDATA ipdata = IPDATA( );
		GetNetWorkIP( _machines[ idx ], &ipdata );

		result += std::to_string( ipdata.d1 );
		result += ".";
		result += std::to_string( ipdata.d2 );
		result += ".";
		result += std::to_string( ipdata.d3 );
		result += ".";
		result += std::to_string( ipdata.d4 );
	}

	return result;
}