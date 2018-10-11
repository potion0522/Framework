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

	_keycode[ "0"     ] = KEY_INPUT_0         ;
	_keycode[ "1"     ] = KEY_INPUT_1         ;
	_keycode[ "2"     ] = KEY_INPUT_2         ;
	_keycode[ "3"     ] = KEY_INPUT_3         ;
	_keycode[ "4"     ] = KEY_INPUT_4         ;
	_keycode[ "5"     ] = KEY_INPUT_5         ;
	_keycode[ "6"     ] = KEY_INPUT_6         ;
	_keycode[ "7"     ] = KEY_INPUT_7         ;
	_keycode[ "8"     ] = KEY_INPUT_8         ;
	_keycode[ "9"     ] = KEY_INPUT_9         ;
	_keycode[ "a"     ] = KEY_INPUT_A         ;
	_keycode[ "b"     ] = KEY_INPUT_B         ;
	_keycode[ "c"     ] = KEY_INPUT_C         ;
	_keycode[ "d"     ] = KEY_INPUT_D         ;
	_keycode[ "e"     ] = KEY_INPUT_E         ;
	_keycode[ "f"     ] = KEY_INPUT_F         ;
	_keycode[ "g"     ] = KEY_INPUT_G         ;
	_keycode[ "h"     ] = KEY_INPUT_H         ;
	_keycode[ "i"     ] = KEY_INPUT_I         ;
	_keycode[ "j"     ] = KEY_INPUT_J         ;
	_keycode[ "k"     ] = KEY_INPUT_K         ;
	_keycode[ "l"     ] = KEY_INPUT_L         ;
	_keycode[ "m"     ] = KEY_INPUT_M         ;
	_keycode[ "n"     ] = KEY_INPUT_N         ;
	_keycode[ "o"     ] = KEY_INPUT_O         ;
	_keycode[ "p"     ] = KEY_INPUT_P         ;
	_keycode[ "q"     ] = KEY_INPUT_Q         ;
	_keycode[ "r"     ] = KEY_INPUT_R         ;
	_keycode[ "s"     ] = KEY_INPUT_S         ;
	_keycode[ "t"     ] = KEY_INPUT_T         ;
	_keycode[ "u"     ] = KEY_INPUT_U         ;
	_keycode[ "v"     ] = KEY_INPUT_V         ;
	_keycode[ "w"     ] = KEY_INPUT_W         ;
	_keycode[ "x"     ] = KEY_INPUT_X         ;
	_keycode[ "y"     ] = KEY_INPUT_Y         ;
	_keycode[ "z"     ] = KEY_INPUT_Z         ;
	_keycode[ " "     ] = KEY_INPUT_SPACE     ;
	_keycode[ "-"     ] = KEY_INPUT_MINUS     ;
	_keycode[ "."     ] = KEY_INPUT_PERIOD    ;
	_keycode[ "/"     ] = KEY_INPUT_SLASH     ;
	_keycode[ "\\"    ] = KEY_INPUT_BACKSLASH ;
	_keycode[ "ENTER" ] = KEY_INPUT_RETURN    ;
	_keycode[ "UP"	  ] = KEY_INPUT_UP        ;
	_keycode[ "DOWN"  ] = KEY_INPUT_DOWN      ;
	_keycode[ "RIGHT" ] = KEY_INPUT_RIGHT     ;
	_keycode[ "LEFT"  ] = KEY_INPUT_LEFT      ;
	_keycode[ "BACK"  ] = KEY_INPUT_BACK      ;
	_keycode[ "F1"    ] = KEY_INPUT_F1        ;
	_keycode[ "F2"    ] = KEY_INPUT_F2        ;
	_keycode[ "F3"    ] = KEY_INPUT_F3        ;
	_keycode[ "F4"    ] = KEY_INPUT_F4        ;
	_keycode[ "F5"    ] = KEY_INPUT_F5        ;
	_keycode[ "F6"    ] = KEY_INPUT_F6        ;
	_keycode[ "F8"    ] = KEY_INPUT_F8        ;
	_keycode[ "F9"    ] = KEY_INPUT_F9        ;
	_keycode[ "F7"    ] = KEY_INPUT_F7        ;
	_keycode[ "F10"   ] = KEY_INPUT_F10       ;
	_keycode[ "F11"   ] = KEY_INPUT_F11       ;
	_keycode[ "F12"   ] = KEY_INPUT_F12       ;

	_keycode_numpad[ "0" ] = KEY_INPUT_NUMPAD0 ;
	_keycode_numpad[ "1" ] = KEY_INPUT_NUMPAD1 ;
	_keycode_numpad[ "2" ] = KEY_INPUT_NUMPAD2 ;
	_keycode_numpad[ "3" ] = KEY_INPUT_NUMPAD3 ;
	_keycode_numpad[ "4" ] = KEY_INPUT_NUMPAD4 ;
	_keycode_numpad[ "5" ] = KEY_INPUT_NUMPAD5 ;
	_keycode_numpad[ "6" ] = KEY_INPUT_NUMPAD6 ;
	_keycode_numpad[ "7" ] = KEY_INPUT_NUMPAD7 ;
	_keycode_numpad[ "8" ] = KEY_INPUT_NUMPAD8 ;
	_keycode_numpad[ "9" ] = KEY_INPUT_NUMPAD9 ;
	_keycode_numpad[ "*" ] = KEY_INPUT_MULTIPLY;
	_keycode_numpad[ "+" ] = KEY_INPUT_ADD     ;
	_keycode_numpad[ "-" ] = KEY_INPUT_SUBTRACT;
	_keycode_numpad[ "." ] = KEY_INPUT_DECIMAL ;
	_keycode_numpad[ "/" ] = KEY_INPUT_DIVIDE  ;
	_keycode_numpad[ "ENTER" ] = KEY_INPUT_NUMPADENTER;
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

int Keyboard::getKeyState( const std::string& key ) const {
	if ( key.empty( ) ) {
		return 0;
	}

	int state = 0;
	// キーが見つかった場合、値を代入
	std::string conv;
	if ( isExistKeyCode( key, conv ) ) {
		int keycode = _keycode.at( conv );
		state = _key_state[ keycode ];
	}

	// numpad
	int state_numpad = 0;
	if ( isExistKeyCodeNumpad( key, conv ) ) {
		int keycode = _keycode_numpad.at( conv );
		state_numpad = _key_state[ keycode ];
	}

	int result = state;
	if ( state == 0 || ( state_numpad != 0 && state_numpad < state ) ) {
		result = state_numpad;
	}

	return result;
}

std::string Keyboard::getString( ) const {
	int keycode = -1;
	int count = -1;
	for ( int i = 0; i < KEY_MAX; i++ ) {
		if ( _key_state[ i ] != 0 ) {
			// 値が最小のキーを取得
			if ( _key_state[ i ] < count || count == -1 ) {
				count = _key_state[ i ];
				keycode = i;
			}
		}
	}

	std::string input;
	// 文字を取得
	if ( keycode != -1 ) {
		for ( std::pair< std::string, int > map : _keycode ) {
			if ( map.second == keycode ) {
				input = map.first;
				break;
			}
		}

		// 取得できなかったらテンキーのキーコードを検索
		if ( input.empty( ) ) {
			for ( std::pair< std::string, int > map : _keycode_numpad ) {
				if ( map.second == keycode ) {
					input = map.first;
					break;
				}
			}
		}

		// 単文字以外は返さない
		if ( input.length( ) != 1 ) {
			input = "";
		}
	}

	return input;
}

bool Keyboard::getKeyUp( const std::string& key ) const {
	if ( key.empty( ) ) {
		return false;
	}

	int size = ( int )_key_up.size( );

	bool key_up = false;

	std::string conv;
	int keycode = -1;
	int keycode_numpad = -1;

	if ( isExistKeyCode( key, conv ) ) {
		keycode = _keycode.at( conv );
	}
	if ( isExistKeyCodeNumpad( key, conv ) ) {
		keycode_numpad = _keycode_numpad.at( conv );
	}

	for ( int key_up_code : _key_up ) {
		if ( key_up_code == keycode || key_up_code == keycode_numpad ) {
			key_up = true;
			break;
		}
	}

	return key_up;
}

bool Keyboard::getKeyDown( const std::string& key ) const {
	if ( key.empty( ) ) {
		return false;
	}

	bool key_down = false;

	std::string conv;
	if ( isExistKeyCode( key, conv ) ) {
		int keycode = _keycode.at( conv );
		if ( _key_state[ keycode ] == 1 ) {
			key_down = true;
		}
	}

	if ( !key_down ) {
		if ( isExistKeyCodeNumpad( key, conv ) ) {
			int keycode = _keycode_numpad.at( conv );
			if ( _key_state[ keycode ] == 1 ) {
				key_down = true;
			}
		}
	}

	return key_down;
}

bool Keyboard::isExistKeyCode( const std::string& find_key, std::string& output ) const {
	bool exist = true;

	std::string find = find_key;
	if ( _keycode.find( find ) == _keycode.end( ) ) {
		// 小文字にする
		std::transform( find.cbegin( ), find.cend( ), find.begin( ), tolower );
		if ( _keycode.find( find ) == _keycode.end( ) ) {
			exist = false;
		}
	}

	if ( exist ) {
		output = find;
	}

	return exist;
}

bool Keyboard::isExistKeyCodeNumpad( const std::string& find_key, std::string& output ) const {
	bool exist = true;

	std::string find = find_key;
	if ( _keycode_numpad.find( find ) == _keycode_numpad.end( ) ) {
		// 小文字にする
		std::transform( find.cbegin( ), find.cend( ), find.begin( ), tolower );
		if ( _keycode_numpad.find( find ) == _keycode_numpad.end( ) ) {
			exist = false;
		}
	}

	if ( exist ) {
		output = find;
	}

	return exist;
}