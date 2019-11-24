#pragma once
#include "Mathematics.h"
#include "smart_ptr.h"
#include <functional>
/*******************************************

�{�^���@�\���܂Ƃ߂��N���X
�����O��Drawer��Mouse��Manager��add���Ă����K�v������

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

	// �����蔻���`��
	void drawCollider( ) const;

public:
	void setPos( const Vector& pos );
	void setAlpha( unsigned char alpha );
	void setRotate( double radian );

	// �����蔻��̕�(Default�͉摜�T�C�Y)
	void setCollisionSize( int width, int height );

	// �{�^���C���[�W
	void setDefaultImage( const char* path );
	void setPushImage( const char* path );

	// ��Ԃ̃��t���b�V��
	void refreshState( );

	// mouse���{�^����ɂ��邩�ǂ���
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
	// �������팸�̂��ߕK�v�ȃ^�C�~���O�̂ݕۗL
	std::shared_ptr< Matrix > _mat_rot;

	ImagePtr _default_image;
	ImagePtr _push_image;
};

