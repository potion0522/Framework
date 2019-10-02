#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( Book );
PTR( ModelMV1 );

/**************************************************

	本のアニメーションなどの管理を行う
	ページ自体は関係ない

**************************************************/

class Book {
private:
	enum ANIM {
		ANIM_NONE,
		ANIM_CLOSING,
		ANIM_OPENING
	};

public:
	Book( );
	virtual ~Book( );

public:
	void update( );
	void draw( ) const;
	void setClose( );
	void setOpen( );
	Vector getSize( ) const;

private:
	void actOnClosing( );
	void actOnOpening( );
	void setAnim( ANIM anim );
	int getDeltaMilliTime( ) const;

private:
	ANIM _anim;
	int _time;

	Matrix _rotate;
	Matrix _page_open_matrix;

	Vector _book_left_pos;
	Vector _book_right_pos;

	ModelMV1Ptr _book_left;
	ModelMV1Ptr _book_right;
};

