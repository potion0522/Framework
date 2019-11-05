#pragma once
#include "smart_ptr.h"
#include "Image.h"

class Screen {
public:
	struct Scope {
	friend class Screen;

	private:
		Scope( );
	public:
		~Scope( );
	};

public:
	Screen( int width, int height );
	virtual ~Screen( );

public:
	Scope createScope( ) const;
	void setDrawScreen( const Scope& scope ) const;
	int getHandle( ) const;

private:
	int _handle;
};

