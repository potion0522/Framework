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
	_key_string[ KEY_INPUT_0         ] = "0";
	_key_string[ KEY_INPUT_1         ] = "1";
	_key_string[ KEY_INPUT_2         ] = "2";
	_key_string[ KEY_INPUT_3         ] = "3";
	_key_string[ KEY_INPUT_4         ] = "4";
	_key_string[ KEY_INPUT_5         ] = "5";
	_key_string[ KEY_INPUT_6         ] = "6";
	_key_string[ KEY_INPUT_7         ] = "7";
	_key_string[ KEY_INPUT_8         ] = "8";
	_key_string[ KEY_INPUT_9         ] = "9";
	_key_string[ KEY_INPUT_A         ] = "a";
	_key_string[ KEY_INPUT_B         ] = "b";
	_key_string[ KEY_INPUT_C         ] = "c";
	_key_string[ KEY_INPUT_D         ] = "d";
	_key_string[ KEY_INPUT_E         ] = "e";
	_key_string[ KEY_INPUT_F         ] = "f";
	_key_string[ KEY_INPUT_G         ] = "g";
	_key_string[ KEY_INPUT_H         ] = "h";
	_key_string[ KEY_INPUT_I         ] = "i";
	_key_string[ KEY_INPUT_J         ] = "j";
	_key_string[ KEY_INPUT_K         ] = "k";
	_key_string[ KEY_INPUT_L         ] = "l";
	_key_string[ KEY_INPUT_M         ] = "m";
	_key_string[ KEY_INPUT_N         ] = "n";
	_key_string[ KEY_INPUT_O         ] = "o";
	_key_string[ KEY_INPUT_P         ] = "p";
	_key_string[ KEY_INPUT_Q         ] = "q";
	_key_string[ KEY_INPUT_R         ] = "r";
	_key_string[ KEY_INPUT_S         ] = "s";
	_key_string[ KEY_INPUT_T         ] = "t";
	_key_string[ KEY_INPUT_U         ] = "u";
	_key_string[ KEY_INPUT_V         ] = "v";
	_key_string[ KEY_INPUT_W         ] = "w";
	_key_string[ KEY_INPUT_X         ] = "x";
	_key_string[ KEY_INPUT_Y         ] = "y";
	_key_string[ KEY_INPUT_Z         ] = "z";
	_key_string[ KEY_INPUT_MINUS     ] = "-";
	_key_string[ KEY_INPUT_PERIOD    ] = ".";
	_key_string[ KEY_INPUT_SLASH     ] = "/";
	_key_string[ KEY_INPUT_BACKSLASH ] = "\\";
	_key_string[ KEY_INPUT_RETURN    ] = "ENTER";
	_key_string[ KEY_INPUT_UP        ] = "UP_ARROW";
	_key_string[ KEY_INPUT_DOWN	     ] = "DOWN_ARROW";
	_key_string[ KEY_INPUT_RIGHT     ] = "RIGHT_ARROW";
	_key_string[ KEY_INPUT_LEFT	     ] = "LEFT_ARROW";
	_key_string[ KEY_INPUT_SPACE     ] = "SPACE";

	_key_state[ "0" ] = 0;
	_key_state[ "1" ] = 0;
	_key_state[ "2" ] = 0;
	_key_state[ "3" ] = 0;
	_key_state[ "4" ] = 0;
	_key_state[ "5" ] = 0;
	_key_state[ "6" ] = 0;
	_key_state[ "7" ] = 0;
	_key_state[ "8" ] = 0;
	_key_state[ "9" ] = 0;
	_key_state[ "a" ] = 0;
	_key_state[ "b" ] = 0;
	_key_state[ "c" ] = 0;
	_key_state[ "d" ] = 0;
	_key_state[ "e" ] = 0;
	_key_state[ "f" ] = 0;
	_key_state[ "g" ] = 0;
	_key_state[ "h" ] = 0;
	_key_state[ "i" ] = 0;
	_key_state[ "j" ] = 0;
	_key_state[ "k" ] = 0;
	_key_state[ "l" ] = 0;
	_key_state[ "m" ] = 0;
	_key_state[ "n" ] = 0;
	_key_state[ "o" ] = 0;
	_key_state[ "p" ] = 0;
	_key_state[ "q" ] = 0;
	_key_state[ "r" ] = 0;
	_key_state[ "s" ] = 0;
	_key_state[ "t" ] = 0;
	_key_state[ "u" ] = 0;
	_key_state[ "v" ] = 0;
	_key_state[ "w" ] = 0;
	_key_state[ "x" ] = 0;
	_key_state[ "y" ] = 0;
	_key_state[ "z" ] = 0;
	_key_state[ "-" ] = 0;
	_key_state[ "." ] = 0;
	_key_state[ "/" ] = 0;
	_key_state[ "*" ] = 0;
	_key_state[ "+" ] = 0;
	_key_state[ "-" ] = 0;
	_key_state[ "." ] = 0;
	_key_state[ "/" ] = 0;
	_key_state[ " " ] = 0;
	_key_state[ "\\" ] = 0;
	_key_state[ "_" ] = 0;
	_key_state[ "ENTER" ] = 0;
	_key_state[ "UP_ARROW" ] = 0;
	_key_state[ "DOWN_ARROW" ] = 0;
	_key_state[ "RIGHT_ARROW" ] = 0;
	_key_state[ "LEFT_ARROW" ] = 0;
	_key_state[ "SPACE" ] = 0;

	//テンキー
	_numpad_string[ KEY_INPUT_NUMPAD0   ] = "0";
	_numpad_string[ KEY_INPUT_NUMPAD1   ] = "1";
	_numpad_string[ KEY_INPUT_NUMPAD2   ] = "2";
	_numpad_string[ KEY_INPUT_NUMPAD3   ] = "3";
	_numpad_string[ KEY_INPUT_NUMPAD4   ] = "4";
	_numpad_string[ KEY_INPUT_NUMPAD5   ] = "5";
	_numpad_string[ KEY_INPUT_NUMPAD6   ] = "6";
	_numpad_string[ KEY_INPUT_NUMPAD7   ] = "7";
	_numpad_string[ KEY_INPUT_NUMPAD8   ] = "8";
	_numpad_string[ KEY_INPUT_NUMPAD9   ] = "9";
	_numpad_string[ KEY_INPUT_MULTIPLY  ] = "*";
	_numpad_string[ KEY_INPUT_ADD       ] = "+";
	_numpad_string[ KEY_INPUT_SUBTRACT  ] = "-";
	_numpad_string[ KEY_INPUT_DECIMAL   ] = ".";
	_numpad_string[ KEY_INPUT_DIVIDE    ] = "/";

	_numpad_state[ "0" ] = 0;
	_numpad_state[ "1" ] = 0;
	_numpad_state[ "2" ] = 0;
	_numpad_state[ "3" ] = 0;
	_numpad_state[ "4" ] = 0;
	_numpad_state[ "5" ] = 0;
	_numpad_state[ "6" ] = 0;
	_numpad_state[ "7" ] = 0;
	_numpad_state[ "8" ] = 0;
	_numpad_state[ "9" ] = 0;
	_numpad_state[ "*" ] = 0;
	_numpad_state[ "+" ] = 0;
	_numpad_state[ "-" ] = 0;
	_numpad_state[ "." ] = 0;
	_numpad_state[ "/" ] = 0;

	//エンターなどのコマンドキー
	_command[ KEY_INPUT_BACK   ] = 0;
	_command[ KEY_INPUT_LSHIFT ] = 0;
	_command[ KEY_INPUT_F1     ] = 0;
	_command[ KEY_INPUT_F2     ] = 0;
	_command[ KEY_INPUT_F3     ] = 0;
	_command[ KEY_INPUT_F4     ] = 0;
	_command[ KEY_INPUT_F5     ] = 0;
	_command[ KEY_INPUT_F6     ] = 0;
	_command[ KEY_INPUT_F7     ] = 0;
	_command[ KEY_INPUT_F8     ] = 0;
	_command[ KEY_INPUT_F9     ] = 0;
	_command[ KEY_INPUT_F10    ] = 0;
	_command[ KEY_INPUT_F11    ] = 0;
	_command[ KEY_INPUT_F12    ] = 0;
}

Keyboard::~Keyboard( ) {
}

void Keyboard::initialize( ) {
}

void Keyboard::finalize( ) {
}

void Keyboard::update( ) {
	std::vector< std::string >( ).swap( _key_up );

	char key_c[ KEY_MAX ] = { };
	GetHitKeyStateAll( key_c );

	for ( int i = 0; i < KEY_MAX; i++ ) {
		//通常キー
		if ( _key_string.find( i ) != _key_string.end( ) ) {
			std::string str = _key_string[ i ];

			if ( _key_state.find( str ) == _key_state.end( ) ) {
				errno_t not_find_keycode = 0;
				assert( not_find_keycode );
			}

			if ( key_c[ i ] ) {
				//アンダーバーだけ特殊
				if ( CheckHitKey( KEY_INPUT_LSHIFT ) && str == "\\" ) {
					str = "_";
				}
				_key_state[ str ]++;
			} else {
				//アンダーバーだけ特殊
				if ( CheckHitKey( KEY_INPUT_LSHIFT ) && str == "\\" ) {
					str = "_";
				}

				if ( _key_state[ str ] != 0 ) {
					_key_up.push_back( str );
				}
				_key_state[ str ] = 0;
			}
		}

		//テンキー
		if ( _numpad_string.find( i ) != _numpad_string.end( ) ) {
			std::string str = _numpad_string[ i ];

			if ( _numpad_state.find( str ) == _numpad_state.end( ) ) {
				errno_t not_find_keycode = 0;
				assert( not_find_keycode );
			}

			if ( key_c[ i ] ) {
				_numpad_state[ str ]++;
			} else {
				if ( _numpad_state[ str ] != 0 ) {
					_key_up.push_back( str );
				}
				_numpad_state[ str ] = 0;
			}
		}

		//エンターなど
		if ( _command.find( i ) != _command.end( ) ) {
			if ( key_c[ i ] ) {
				_command[ i ]++;
			} else {
				_command[ i ] = 0;
			}
		}
	}

	//テンキーの情報と統合する
	std::unordered_map< std::string, int >::iterator ite;
	ite = _numpad_state.begin( );
	for ( ite; ite != _numpad_state.end( ); ite++ ) {
		std::string str = ite->first;
		int num = ite->second;

		//大きいほうを優先
		if ( _key_state[ str ] < num ) {
			_key_state[ str ] = num;
		}
	}
}

int Keyboard::getState( std::string key ) const {

	std::string str = key;

	// ENTERとかではない場合は小文字で検索
	if ( str.length( ) <= 1 ) {
		std::transform( str.cbegin( ), str.cend( ), str.begin( ), tolower );
	}

	if ( _key_state.find( str ) != _key_state.end( ) ) {
		return _key_state.find( str )->second;
	}
	return 0;
}

std::string Keyboard::getString( ) const {
	std::unordered_map< std::string, int >::const_iterator ite;
	ite = _key_state.begin( );

	// 押されているキーを走査
	for ( ite; ite != _key_state.end( ); ite++ ) {
		// エンターとかならコンティニュー
		if ( ite->first.length( ) > 1 ) {
			continue;
		}

		if ( ite->second == 1 ) {

			// シフト、ファンクションなど特殊キーを見ていく
			std::unordered_map< int, int >::const_iterator command_ite;
			command_ite = _command.find( KEY_INPUT_LSHIFT );
			if ( command_ite->second > 0 ) {
				//大文字
				std::string key = ite->first;
				std::transform( key.cbegin( ), key.cend( ), key.begin( ), toupper );
				return key;
			}
			return ite->first;
		}
	}

	return "";
}

bool Keyboard::getKeyUp( std::string key ) const {
	std::string str = key;

	// ENTERとかではない場合は小文字で検索
	if ( str.length( ) <= 1 ) {
		std::transform( str.cbegin( ), str.cend( ), str.begin( ), tolower );
	}

	int size = ( int )_key_up.size( );
	for ( int i = 0; i < size; i++ ) {
		if ( _key_up[ i ] == str ) {
			return true;
		}
	}

	return false;
}

bool Keyboard::getKeyDown( std::string key ) const {
	if ( key == "_" ) {
		return true;
	}

	std::string str = key;

	// ENTERとかではない場合は小文字で検索
	if ( str.length( ) <= 1 ) {
		std::transform( str.cbegin( ), str.cend( ), str.begin( ), tolower );
	}
	
	if ( _key_state.find( str ) != _key_state.end( ) ) {
		if ( _key_state.find( str )->second == 1 ) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

bool Keyboard::isKeyDownFunction( int num ) const {
	int code = KEY_INPUT_F1;
	switch ( num ) {
	case 2 : code = KEY_INPUT_F2 ; break;
	case 3 : code = KEY_INPUT_F3 ; break;
	case 4 : code = KEY_INPUT_F4 ; break;
	case 5 : code = KEY_INPUT_F5 ; break;
	case 6 : code = KEY_INPUT_F6 ; break;
	case 7 : code = KEY_INPUT_F7 ; break;
	case 8 : code = KEY_INPUT_F8 ; break;
	case 9 : code = KEY_INPUT_F9 ; break;
	case 10: code = KEY_INPUT_F10; break;
	case 11: code = KEY_INPUT_F11; break;
	case 12: code = KEY_INPUT_F12; break;
	default: 
		break;
	}

	return ( _command.find( code )->second == 1 );
}

int Keyboard::getBackSpace( ) const {
	return _command.find( KEY_INPUT_BACK )->second;
}
