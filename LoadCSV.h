#pragma once
#include <vector>
#include <string>
/*******************************************

	CSVデータの読み込み、
	読み込んだデータを保持

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
		// データのクリア
		clear( );
		
		FILE* fp;
		if ( fopen_s( &fp, file_path, "rb" ) != 0 ) {
			// error
			return;
		}

		// 1行のデータ
		std::vector< std::string > row_data;
		// 単語ごとのデータ
		std::string word_data;

		char c = '\0';
		bool loop = true;
		while ( loop ) {
			// データの読み込み
			c = getc( fp );

			// 読み取った文字に対して処理を変える
			switch ( c ) {
			case ',': // 単語区切り
				row_data.push_back( word_data );
				word_data.clear( );
				break;

			case '\n': // 行末
				row_data.push_back( word_data );
				data.push_back( row_data );
				row_data.clear( );
				word_data.clear( );
				break;

			case EOF: // 終了
				loop = false;
				data.push_back( row_data );
				break;

			default: // 文字追加
				word_data += c;
				break;
			}
		}

		fclose( fp );
	}
};
