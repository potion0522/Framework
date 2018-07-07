#include "Manager.h"
#include "Base.h"
#include "DxSetting.h"

ManagerPtr Manager::_instance;

Manager::Manager( ) :
_fin( false ) {
	_setting = DxSettingPtr( new DxSetting( ) );
}

Manager::~Manager( ) {
	std::map< std::string, BasePtr >::iterator ite;
	ite = _exe.begin( );

	for ( ite; ite != _exe.end( ); ite++ ) {
		ite->second->finalize( );
	}

	_setting->finalize( );
}

ManagerPtr Manager::getInstance( ) {
	return _instance;
}

void Manager::initialize( ) {
	if ( !_instance ) {
		_instance = ManagerPtr( new Manager( ) );
	}
}

void Manager::finalize( ) {
	if ( _instance ) {
		_instance.reset( );
	}
}

void Manager::allInitialize( ) {
	std::map< std::string, BasePtr >::iterator ite;
	ite = _exe.begin( );

	for ( ite; ite != _exe.end( ); ite++ ) {
		ite->second->initialize( );
	}
}

void Manager::update( ) {
	std::map< std::string, BasePtr >::iterator ite;
	ite = _exe.begin( );

	for ( ite; ite != _exe.end( ); ite++ ) {
		ite->second->update( );
	}
}

void Manager::add( std::string tag, BasePtr ptr ) {
	_exe[ tag ] =  ptr;
}

BasePtr Manager::getTask( std::string tag ) {
	if ( _exe.find( tag ) == _exe.end( ) ) {
		return BasePtr( );
	}

	return _exe[ tag ];
}

bool Manager::isFin( ) const {
	return _fin;
}

void Manager::setWindowSize( int width, int height ) {
	_setting->setWindowSize( width, height );
}

void Manager::setScreenSize( int width, int height ) {
	_setting->setGraphMode( width, height );
}

void Manager::changeWindowMode( bool flag ) {
	_setting->changeWindowMode( flag );
}

int Manager::getWindowWidth ( ) const {
	return _setting->getWindowWidth( );
}

int Manager::getWindowHeight( ) const {
	return _setting->getWindowHeight( );
}

int Manager::getScreenWidth ( ) const {
	return _setting->getScreenWidth( );
}

int Manager::getScreenHeight( ) const {
	return _setting->getScreenHeight( );
}