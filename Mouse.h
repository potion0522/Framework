#pragma once
#include "Task.h"
#include "Mathematics.h"
#include <string>
/*******************************************

	マウスの入力を監視し、結果を返す

*******************************************/

PTR( Mouse );

class Mouse : public Task {
public:
	static MousePtr getTask( );
	static std::string getTag( ) { return "MOUSE"; }

public:
	Mouse( );
	virtual ~Mouse( );

public:
	void initialize( );
	void update( );

private:
	void updateClickingLeft( const int& mouse_data );
	void updateClickingRight( const int& mouse_data );

public:
	void setMouseDraw( bool flag );
	Vector getPoint( ) const;
	bool isClickDownLeft( ) const;
	bool isClickDownRight( ) const;
	bool isClickUpLeft( ) const;
	bool isClickUpRight( ) const;
	int getClickingLeft( ) const;
	int getClickingRight( ) const;
	void setMousePoint( const int& x, const int& y );

private:
	unsigned short _click_left;
	unsigned short _click_right;
	bool _clickup_left;
	bool _clickup_right;
};

