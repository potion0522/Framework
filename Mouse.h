#pragma once
#include "Base.h"
#include "Vector.h"
#include <string>

PTR( Mouse );

class Mouse : public Base {
public:
	static MousePtr getTask( );
	static std::string getTag( );

public:
	Mouse( );
	virtual ~Mouse( );

public:
	void initialize( );
	void update( );

private:
	void calcLeftClick( );
	void calcRightClick( );

public:
	Vector getPoint( ) const;
	bool isClickDownLeft( ) const;
	bool isClickDownRight( ) const;
	bool isClickUpLeft( ) const;
	bool isClickUpRight( ) const;
	int getClickingLeft( ) const;
	int getClickingRight( ) const;

private:
	Vector _pos;
	int _mouse;
	int _click_left;
	int _click_right;
	bool _clickup_left;
	bool _clickup_right;
};

