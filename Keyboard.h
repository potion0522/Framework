#pragma once
#include "Base.h"
#include <unordered_map>
#include <string>
#include <vector>

PTR( Keyboard );

class Keyboard : public Base {
public:
	static KeyboardPtr getTask( );
	static std::string getTag( ) { return "KEYBOARD"; }

public:
	Keyboard( );
	virtual ~Keyboard( );

public:
	void initialize( );
	void finalize( );
	void update( );

public:
	int getKeyState( const std::string& key ) const;
	std::string getString( ) const;
	bool getKeyUp( const std::string& key ) const;
	bool getKeyDown( const std::string& key ) const;

private:
	// ƒL[ŒŸõBŒ©‚Â‚©‚Á‚½ê‡•ÏŠ·Œã‚Ì•¶š‚ª‘æ“ñˆø”‚É‘ã“ü‚³‚ê‚é
	bool isExistKeyCode( const std::string& find_key, std::string& output ) const;
	bool isExistKeyCodeNumpad( const std::string& find_key, std::string& output ) const;

private:
	static const int KEY_MAX = 256;
	int _key_state[ KEY_MAX ];
	std::unordered_map< std::string, int > _keycode;
	std::unordered_map< std::string, int > _keycode_numpad;
	std::vector< int > _key_up;
};

