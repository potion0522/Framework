#include "Keyboard.h"
#include "DxLib.h"
#include "Manager.h"
#include <errno.h>
#include <assert.h>
#include <algorithm>

const int KEY_MAX = 256;

KeyboardPtr Keyboard::getTask( ) {
	return std::dynamic_pointer_cast< Keyboard >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Keyboard::Keyboard( ) {
	memset( _key_state, 0, sizeof( int ) * KEY_MAX );

	_key_code[ "0"     ] = KEY_INPUT_0         ;
	_key_code[ "1"     ] = KEY_INPUT_1         ;
	_key_code[ "2"     ] = KEY_INPUT_2         ;
	_key_code[ "3"     ] = KEY_INPUT_3         ;
	_key_code[ "4"     ] = KEY_INPUT_4         ;
	_key_code[ "5"     ] = KEY_INPUT_5         ;
	_key_code[ "6"     ] = KEY_INPUT_6         ;
	_key_code[ "7"     ] = KEY_INPUT_7         ;
	_key_code[ "8"     ] = KEY_INPUT_8         ;
	_key_code[ "9"     ] = KEY_INPUT_9         ;
	_key_code[ "a"     ] = KEY_INPUT_A         ;
	_key_code[ "b"     ] = KEY_INPUT_B         ;
	_key_code[ "c"     ] = KEY_INPUT_C         ;
	_key_code[ "d"     ] = KEY_INPUT_D         ;
	_key_code[ "e"     ] = KEY_INPUT_E         ;
	_key_code[ "f"     ] = KEY_INPUT_F         ;
	_key_code[ "g"     ] = KEY_INPUT_G         ;
	_key_code[ "h"     ] = KEY_INPUT_H         ;
	_key_code[ "i"     ] = KEY_INPUT_I         ;
	_key_code[ "j"     ] = KEY_INPUT_J         ;
	_key_code[ "k"     ] = KEY_INPUT_K         ;
	_key_code[ "l"     ] = KEY_INPUT_L         ;
	_key_code[ "m"     ] = KEY_INPUT_M         ;
	_key_code[ "n"     ] = KEY_INPUT_N         ;
	_key_code[ "o"     ] = KEY_INPUT_O         ;
	_key_code[ "p"     ] = KEY_INPUT_P         ;
	_key_code[ "q"     ] = KEY_INPUT_Q         ;
	_key_code[ "r"     ] = KEY_INPUT_R         ;
	_key_code[ "s"     ] = KEY_INPUT_S         ;
	_key_code[ "t"     ] = KEY_INPUT_T         ;
	_key_code[ "u"     ] = KEY_INPUT_U         ;
	_key_code[ "v"     ] = KEY_INPUT_V         ;
	_key_code[ "w"     ] = KEY_INPUT_W         ;
	_key_code[ "x"     ] = KEY_INPUT_X         ;
	_key_code[ "y"     ] = KEY_INPUT_Y         ;
	_key_code[ "z"     ] = KEY_INPUT_Z         ;
	_key_code[ "-"     ] = KEY_INPUT_MINUS     ;
	_key_code[ "."     ] = KEY_INPUT_PERIOD    ;
	_key_code[ "/"     ] = KEY_INPUT_SLASH     ;
	_key_code[ "\\"    ] = KEY_INPUT_BACKSLASH ;
	_key_code[ "ENTER" ] = KEY_INPUT_RETURN    ;
	_key_code[ "UP"	   ] = KEY_INPUT_UP        ;
	_key_code[ "DOWN"  ] = KEY_INPUT_DOWN	   ;
	_key_code[ "RIGHT" ] = KEY_INPUT_RIGHT     ;
	_key_code[ "LEFT"  ] = KEY_INPUT_LEFT	   ;
	_key_code[ "SPACE" ] = KEY_INPUT_SPACE     ;
	_key_code[ "BACK"  ] = KEY_INPUT_BACK      ;
	_key_code[ "F1"    ] = KEY_INPUT_F1        ;
	_key_code[ "F2"    ] = KEY_INPUT_F2        ;
	_key_code[ "F3"    ] = KEY_INPUT_F3        ;
	_key_code[ "F4"    ] = KEY_INPUT_F4        ;
	_key_code[ "F5"    ] = KEY_INPUT_F5        ;
	_key_code[ "F6"    ] = KEY_INPUT_F6        ;
	_key_code[ "F8"    ] = KEY_INPUT_F8        ;
	_key_code[ "F9"    ] = KEY_INPUT_F9        ;
	_key_code[ "F7"    ] = KEY_INPUT_F7        ;
	_key_code[ "F10"   ] = KEY_INPUT_F10       ;
	_key_code[ "F11"   ] = KEY_INPUT_F11       ;
	_key_code[ "F12"   ] = KEY_INPUT_F12       ;
}

Keyboard::~Keyboard( ) {
}

void Keyboard::initialize( ) {
}

void Keyboard::finalize( ) {
}

void Keyboard::update( ) {
	std::vector< int >( ).swap( _key_up );
	char key[ KEY_MAX ] = { };
	GetHitKeyStateAll( key );

	for ( int i = 0; i < KEY_MAX; i++ ) {
		if ( key[ i ] ) {
			_key_state[ i ]++;
		} else {
			// 離した瞬間の保存
			if ( _key_state[ i ] != 0 ) {
				_key_up.push_back( i );
			}

			_key_state[ i ] = 0;
		}
	}
}

int Keyboard::getKeyState( std::string key ) const {
	int state = 0;
	// キーが見つかった場合、値を代入
	std::string conv;
	if ( isExistKeyCode( key, conv ) ) {
		int key_code = _key_code.at( conv );
		state = _key_state[ key_code ];
	}

	return state;
}

std::string Keyboard::getString( ) const {
	int key_code = -1;
	int count = -1;
	for ( int i = 0; i < KEY_MAX; i++ ) {
		if ( _key_state[ i ] != 0 ) {
			// 値が最小のキーを取得
			if ( _key_state[ i ] < count || count == -1 ) {
				count = _key_state[ i ];
				key_code = i;
			}
		}
	}

	std::string input;
	// 文字を取得
	if ( key_code != -1 ) {
		for ( std::pair< std::string, int > map : _key_code ) {
			if ( map.second == key_code ) {
				input = map.first;
				break;
			}
		}

		// 単文字以外は返さない
		if ( input.length( ) != 1 ) {
			input = "";
		}
	}

	return input;
}

bool Keyboard::getKeyUp( std::string key ) const {
	int size = ( int )_key_up.size( );

	bool key_up = false;

	std::string conv;
	if ( isExistKeyCode( key, conv ) ) {
		int key_code = _key_code.at( conv );

		for ( int i = 0; i < size; i++ ) {
			if ( _key_up[ i ] == key_code ) {
				key_up = true;
				break;
			}
		}
	}

	return key_up;
}

bool Keyboard::getKeyDown( std::string key ) const {
	bool key_down = false;

	std::string conv;
	if ( isExistKeyCode( key, conv ) ) {
		int key_code = _key_code.at( conv );
		if ( _key_state[ key_code ] == 1 ) {
			key_down = true;
		}
	}

	return key_down;
}

bool Keyboard::isExistKeyCode( std::string find_key, std::string &conv_key ) const {
	bool exist = true;

	std::string find = find_key;
	if ( _key_code.find( find ) == _key_code.end( ) ) {
		// 小文字にする
		std::transform( find.cbegin( ), find.cend( ), find.begin( ), tolower );
		if ( _key_code.find( find ) == _key_code.end( ) ) {
			exist = false;
		}
	}

	if ( exist ) {
		conv_key = find;
	}

	return exist;
}