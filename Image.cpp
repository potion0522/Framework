#include "Image.h"
#include "DxLib.h"
#include <errno.h>
#include <assert.h>
#include <Windows.h>

Image::Image( std::string path ) :
_path( path ) {
	if ( path == "" ) {
		return;
	}
	findFile( _path );
}

Image::~Image( ) {
}

int Image::getImage( std::string file_name ) const {
	if ( _images.find( file_name ) != _images.end( ) ) {
		return _images.find( file_name )->second.handle;
	}
	return -1;
}

int Image::getImageWidth( std::string file_name ) const {
	if ( _images.find( file_name ) != _images.end( ) ) {
		return _images.find( file_name )->second.width;
	}
	return -1;
}

int Image::getImageHeight( std::string file_name ) const {
	if ( _images.find( file_name ) != _images.end( ) ) {
		return _images.find( file_name )->second.height;
	}
	return -1;
}

void Image::findFile( std::string path ) {
	WIN32_FIND_DATA data;
	HANDLE handle;

	path += "/";

	handle = FindFirstFile( ( path + "*" ).c_str( ), &data );

	errno_t find_handle = ( handle != INVALID_HANDLE_VALUE );
	assert( find_handle );

	do {
		
		if ( ( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) ) {
		//ディレクトリ	                  
			std::string file_name = data.cFileName;
			if ( file_name != "." && file_name != ".." ) {
				//再起(サブディレクトリ検索)
				findFile( ( path + file_name ) );
			}

		} else {
		//ファイル
			//名前
			std::string file_name = data.cFileName;
			std::string file_extension = data.cFileName;

			{//ファイル名を取得
				file_name = file_name.substr( 0, file_name.find_last_of( "." ) );
			}

			{//拡張子を取得
				int pos = ( int )file_extension.find_last_of( "." ) + 1;
				file_extension = file_extension.substr( pos, file_extension.length( ) - pos );
			}

			//拡張子を識別し、画像ロード
			if ( file_extension == "png" || file_extension == "jpg" || file_extension == "jpeg" ) {
				_images[ file_name ].handle = LoadGraph( ( path + data.cFileName ).c_str( ) );
				GetGraphSize( _images[ file_name ].handle, &_images[ file_name ].width, &_images[ file_name ].height );
			}
		}

	} while ( FindNextFile( handle, &data ) );

	FindClose( handle );
}