#pragma once
#include "smart_ptr.h"
#include "Base.h"
#include <vector>
#include <string>

PTR( Random );

/*

　メルセンヌ・ツイスタを使用

*/

class Random : public Base {
public:
	static RandomPtr getTask( );
	static std::string getTag( );

public:
	Random( );
	virtual ~Random( );

public:
	void initialize( );
	void update( );

public:
	void setIgnore( unsigned long ignore );
	void setIgnore( double ignore );
	void resetIgnore( );

public:
	// 32ビット長整数 0x0以上0xffffffff以下
	unsigned long getInt32( ) const;
	unsigned long getInt32( unsigned long range_min, unsigned long range_max ) const;
	// 31ビット長整数 0x0以上0x7fffffff以下
	long getInt31( ) const;
	
	// 一様実乱数(32ビット精度) 0以上1以下
	double getRealOne( ) const;

	// 一様実乱数(32ビット精度) 0以上1未満
	double getRealTwo( ) const;

	// 一様実乱数(32ビット精度) 0より大きく1未満
	double getRealThree( ) const;

	// 一様実乱数(53ビット精度) 0以上1未満
	double getRes53( ) const;

private:
	bool isReplay( unsigned long num ) const;
	bool isReplay( double num ) const;

private:
	std::vector< unsigned long > _ignore_long;
	std::vector< double > _ignore_double;
};

