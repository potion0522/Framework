#pragma once

/*
	�{�^���Ȃǂ������ꂽ�Ƃ��� activate ���Ă΂��
	���̃N���X���p�����ăC�x���g���쐬����
*/

class Event {
public:
	Event( ) { };

	virtual ~Event( ) { };

public:
	virtual void activate( ) = 0;
};

