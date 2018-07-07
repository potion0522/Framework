#pragma once
#include "smart_ptr.h"
#include <string>
#include <unordered_map>

PTR( Image );

struct ImageProperty {
	int width;
	int height;
	int handle;
};

class Image {
public:
	Image( std::string path );
	virtual ~Image( );

public:
	void findFile( std::string path );
	int getImage( std::string file_name ) const;
	int getImageWidth( std::string file_name ) const;
	int getImageHeight( std::string file_name ) const;

private:
	std::string _path;
	std::unordered_map< std::string, ImageProperty > _images;
};

