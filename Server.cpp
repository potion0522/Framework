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
_recieving_tcp( false ) {
	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		_machines[ i ] = -1;
	}

	PreparationListenNetWork( TCP_PORT );
}

Server::~Server( ) {
}

void Server::initialize( ) {
}

void Server::finalize( ) {
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
	int result = -1;

	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		if ( _machines[ i ] != -1 ) {
			result = NetWorkSend( _machines[ i ], data->getPtr( ), data->getSize( ) );
		}
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
	_recieving_tcp = false;

	for ( int i = 0; i < MAX_MACHINES; i++ ) {
		if ( _machines[ i ] == -1 ) {
			continue;
		}

		int result = NetWorkRecv( _machines[ i ], _recvdata_tcp->getPtr( ), _recvdata_tcp->getSize( ) );

		if ( result == 0 ) {
			_recieving_tcp = true;
			break;
		}
	}
}

bool Server::isRecievingTcp( ) const {
	return _recieving_tcp;
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