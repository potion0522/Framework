#include "Server.h"
#include "Manager.h"
#include "DxLib.h"

const int UDP_PORT = 8000; //“K“–

ServerPtr Server::getTask( ) {
	return std::dynamic_pointer_cast< Server >( Manager::getInstance( )->getTask( getTag( ) ) );
}

std::string Server::getTag( ) {
	return "SERVER";
}

Server::Server( ) {
	PreparationListenNetWork( UDP_PORT );
}

Server::~Server( ) {
}

void Server::initialize( ) {
}

void Server::finalize( ) {
}

void Server::update( ) {
}