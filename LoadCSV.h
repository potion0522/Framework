#pragma once
#include <vector>
#include <string>
/*******************************************

	CSV�f�[�^�̓ǂݍ��݁A
	�ǂݍ��񂾃f�[�^��ێ�

*******************************************/

struct CsvData {
	std::vector< std::vector< std::string > > data;


	CsvData( ) { }
	CsvData( const char* file_path ) {
		load( file_path );
	}

	inline void clear( ) {
		data.clear( );
	}

	inline void load( const char* file_path ) {
		// �f�[�^�̃N���A
		clear( );
		
		FILE* fp;
		if ( fopen_s( &fp, file_path, "rb" ) != 0 ) {
			// error
			return;
		}

		// 1�s�̃f�[�^
		std::vector< std::string > row_data;
		// �P�ꂲ�Ƃ̃f�[�^
		std::string word_data;

		char c = '\0';
		bool loop = true;
		while ( loop ) {
			// �f�[�^�̓ǂݍ���
			c = getc( fp );

			// �ǂݎ���������ɑ΂��ď�����ς���
			switch ( c ) {
			case ',': // �P���؂�
				row_data.push_back( word_data );
				word_data.clear( );
				break;

			case '\n': // �s��
				row_data.push_back( word_data );
				data.push_back( row_data );
				row_data.clear( );
				word_data.clear( );
				break;

			case EOF: // �I��
				loop = false;
				data.push_back( row_data );
				break;

			default: // �����ǉ�
				word_data += c;
				break;
			}
		}

		fclose( fp );
	}
};
