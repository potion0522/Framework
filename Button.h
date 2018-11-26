#pragma once
#include "Vector.h"
#include "smart_ptr.h"
#include "Matrix.h"

PTR( Image );
PTR( Event );

class Button {
public:
	enum STATE {
		STATE_NONE,
		STATE_PUSH,
		STATE_CLICKED,
		STATE_MAX
	};

public:
	Button( );
	virtual ~Button( );

public:
	void update( );
	void draw( ) const;

	// 当たり判定を描画
	void drawCollider( ) const;

public:
	void setPos( const Vector& pos );
	void setAlpha( unsigned char alpha );
	void setRotate( double radian );

	// 当たり判定の幅
	void setCollisionSize( int width, int height );

	// ボタンイメージ
	void setDefaultImage( const char* path );
	void setPushImage( const char* path );

private:
	void updateDefault( );
	void updatePush( );
	void updateClicked( );

private:
	// mouseがボタン上にあるかどうか
	bool onButton( ) const;

public:
	bool isClicked( ) const;

private:
	STATE _state;
	Vector _pos;
	int _width;
	int _height;
	// メモリ削減のため必要なタイミングのみ保有
	std::shared_ptr< Matrix > _mat_rot;

	ImagePtr _default_image;
	ImagePtr _push_image;
};

