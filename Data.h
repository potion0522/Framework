#pragma once

/*******************************************

	�l�b�g���[�N�ʐM�Ɏg�p����N���X
	���̃N���X���p�������N���X���g�p����Client��Server����f�[�^�̑���M������

*******************************************/

class Data {
public:
	Data( ) { };
	virtual ~Data( ) { };

public:
	virtual int getSize( ) const = 0;
	virtual void *getPtr( ) = 0; 
};

