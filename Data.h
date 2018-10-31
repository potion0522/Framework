#pragma once

/*
	ネットワーク通信に使用するクラス
	このクラスを継承したクラスを使用してClientとServerからデータの送受信をする
*/

class Data {
public:
	Data( ) { };
	virtual ~Data( ) { };

public:
	virtual int getSize( ) const = 0;
	virtual void *getPtr( ) = 0; 
};

