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

std::string Server::getTag( ) {
	return "SERVER";
}

Server::Server( DataPtr recvdata_tcp ) :
_recvdata_tcp( recvdata_tcp ),
_handle( -1 ),
_recieving_tcp( false ) {
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

int Server::sendTcp( DataPtr data ) {
	int result = -1;
	if ( _handle != -1 ) {
		result = NetWorkSend( _handle, data->getPtr( ), data->getSize( ) );
	}

	return result;
}

void Server::accept( ) {
	if ( _handle != -1 ) {
		return;
	}

	int handle = GetNewAcceptNetWork( );
	if ( handle == -1 ) {
		return;
	}
	_handle = handle;
}

void Server::lost( ) {
	int handle = GetLostNetWork( );
	if ( handle == -1 ) {
		return;
	}
	if ( handle != _handle ) {
		return;
	}

	CloseNetWork( _handle );
	_handle = -1;
}

void Server::recv( ) {
	recvTcp( );
}

void Server::recvTcp( ) {
	_recieving_tcp = false;
	if ( _handle == -1 ) {
		return;
	}
	int result = NetWorkRecv( _handle, _recvdata_tcp->getPtr( ), _recvdata_tcp->getSize( ) );

	if ( result == 0 ) {
		_recieving_tcp = true;
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

std::string Server::getClientIP( ) const {
	IPDATA ipdata = IPDATA( );
	GetNetWorkIP( _handle, &ipdata );

	std::string result;
	if ( _handle != -1 ) {
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