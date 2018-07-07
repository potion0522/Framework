#pragma once
#include "Base.h"
#include <unordered_map>
#include <vector>
#include <string>

PTR( Keyboard );

class Keyboard : public Base {
public:
	static KeyboardPtr getTask( );
	static std::string getTag( );

public:
	Keyboard( );
	virtual ~Keyboard( );

public:
	void initialize( );
	void finalize( );
	void update( );

public:
	int getState( std::string key ) const;
	std::string getString( ) const;
	bool getKeyUp( std::string key ) const;
	bool getKeyDown( std::string key ) const;
	bool isKeyDownFunction( int num ) const;
	int getBackSpace( ) const;

private:
	std::unordered_map< int, std::string > _key_string;
	std::unordered_map< int, std::string > _numpad_string;
	std::unordered_map< std::string, int > _key_state;
	std::unordered_map< std::string, int > _numpad_state;
	std::unordered_map< int, int > _command;
	std::vector< std::string > _key_up;
};

