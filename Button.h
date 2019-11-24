#pragma once
#include "Mathematics.h"
#include "smart_ptr.h"
#include <functional>
/*******************************************

ボタン機能をまとめたクラス
※事前にDrawerとMouseをManagerにaddしておく必要がある

*******************************************/

PTR( Image );
PTR( Button );

class Button {
public:
	enum STATE {
		STATE_NONE,
		STATE_PUSH,
		STATE_CLICKED,
		STATE_MAX
	};

public:
	Button( const char* tag, std::function< void( const char* ) > callback );
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

	// 当たり判定の幅(Defaultは画像サイズ)
	void setCollisionSize( int width, int height );

	// ボタンイメージ
	void setDefaultImage( const char* path );
	void setPushImage( const char* path );

	// 状態のリフレッシュ
	void refreshState( );

	// mouseがボタン上にあるかどうか
	bool isMouseOnButton( ) const;
	Vector getColliderSize( ) const;

private:
	void updateDefault( );
	void updatePush( );
	void updateClicked( );


private:
	const char* TAG;

private:
	STATE _state;
	Vector _pos;
	int _width;
	int _height;
	std::function< void( const char* ) > _callback;
	// メモリ削減のため必要なタイミングのみ保有
	std::shared_ptr< Matrix > _mat_rot;

	ImagePtr _default_image;
	ImagePtr _push_image;
};

