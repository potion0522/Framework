#pragma once
#include "Base.h"
#include <unordered_map>
#include <string>
#include <vector>
/*******************************************

	キーボードの入力を監視し、結果を返す

*******************************************/

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
	std::string getKey( bool non_return_string = true ) const;
	bool getKeyUp( const std::string& key ) const;
	bool getKeyDown( const std::string& key ) const;

private:
	// キー検索。見つかった場合変換後の文字が第二引数に代入される
	bool isExistKeyCode( const std::string& find_key, std::string& output ) const;
	bool isExistKeyCodeNumpad( const std::string& find_key, std::string& output ) const;

private:
	static const int KEY_MAX = 256;
	int _key_state[ KEY_MAX ];
	std::unordered_map< std::string, int > _keycode;
	std::unordered_map< std::string, int > _keycode_numpad;
	std::vector< int > _key_up;
};

