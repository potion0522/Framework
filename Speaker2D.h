#pragma once
#include "Speaker.h"
/*******************************************

2Dサウンドを鳴らすためのクラス
3Dとははっきり分けたいため、個別の派生クラス

*******************************************/

class Speaker2D : public Speaker {
public:
	Speaker2D( int handle );
	virtual ~Speaker2D( );
};

