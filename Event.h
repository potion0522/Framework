#pragma once

/*
	ボタンなどが押されたときに activate が呼ばれる
	このクラスを継承してイベントを作成する
*/

class Event {
public:
	Event( ) { };
	virtual ~Event( ) { };

public:
	virtual void activate( ) = 0;
};

