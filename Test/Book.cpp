#include "Book.h"
#include "ModelMV1.h"
#include "Manager.h"



const char* BOOK_MODEL_LEFT  = "model/BookLeft.mv1";
const char* BOOK_MODEL_RIGHT = "model/BookRight.mv1";
const char* BOOK_TEXTURE = "texture/Book.png";
const double SCALE = 0.5;
const double ADJUST_OPEN_BOOK_Y = 320.0;
const int ANIM_COMPLETE_MILLI_TIME = 1000 * 3;

Book::Book( ) :
_anim( ANIM_NONE ),
_time( 0 ) {
	_rotate = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI / 2 );

	{ // ¶‘¤
		_book_left = ModelMV1Ptr( new ModelMV1 );
		_book_left->load( BOOK_MODEL_LEFT );
		_book_left->setTexture( BOOK_TEXTURE, 0 );
		_book_left->setDifMaterialColor( 0, 1, 1, 1, 1 );
	}

	{ // ‰E‘¤
		_book_right = ModelMV1Ptr( new ModelMV1 );
		_book_right->load( BOOK_MODEL_RIGHT );
		_book_right->setTexture( BOOK_TEXTURE, 0 );
		_book_right->setDifMaterialColor( 0, 1, 1, 1, 1 );
	}

	setAnim( ANIM_OPENING );
}

Book::~Book( ) {
}

void Book::update( ) {
	switch ( _anim ) {
	case ANIM_NONE:
		break;

	case ANIM_CLOSING:
		actOnClosing( );
		break;

	case ANIM_OPENING:
		actOnOpening( );
		break;
	}
}

void Book::actOnClosing( ) {
	_time += getDeltaMilliTime( );

	double ratio = ( double )_time / ANIM_COMPLETE_MILLI_TIME;
	const double MAX_ROTATE_RADIAN = PI;
	double z_rotate = MAX_ROTATE_RADIAN * ratio;
	double y_pos = ADJUST_OPEN_BOOK_Y * ratio;
	if ( z_rotate > PI ) {
		z_rotate = PI;
	}

	_book_right_pos = Vector( 0, y_pos, 0 );
	_page_open_matrix = _rotate.multiply( Matrix::makeTransformRotation( Vector( 1, 0, 0 ), z_rotate ) );

	if ( _time > ANIM_COMPLETE_MILLI_TIME ) {
		setAnim( ANIM_NONE );
	}
}

void Book::actOnOpening( ) {
	_time += getDeltaMilliTime( );

	double ratio = ( double )_time / ANIM_COMPLETE_MILLI_TIME;
	const double MAX_ROTATE_RADIAN = PI;
	double z_rotate = MAX_ROTATE_RADIAN - MAX_ROTATE_RADIAN * ratio;
	double y_pos = ADJUST_OPEN_BOOK_Y - ADJUST_OPEN_BOOK_Y * ratio;
	if ( z_rotate < 0 ) {
		z_rotate = 0;
	}

	_book_right_pos = Vector( 0, y_pos, 0 );
	_page_open_matrix = _rotate.multiply( Matrix::makeTransformRotation( Vector( 1, 0, 0 ), z_rotate ) );

	if ( _time > ANIM_COMPLETE_MILLI_TIME ) {
		setAnim( ANIM_CLOSING );
	}
}

void Book::draw( ) const {
	{
		Vector size = _book_left->getOriginMeterSize( ) * 1000;
		Vector adjust = Vector( 2000 / size.x, 1, 3000 / size.z );
		Matrix scale = Matrix::makeTransformScaling( adjust );
		_book_left->draw( Vector( ), _rotate.multiply( scale ) );
	}

	{
		Vector size = _book_right->getOriginMeterSize( ) * 1000;
		Vector adjust = Vector( 2000 / size.x, 1, 3000 / size.z );
		Matrix scale = Matrix::makeTransformScaling( adjust );
		_book_right->draw( _book_right_pos * 0.001, _page_open_matrix.multiply( scale ) );
	}
}

void Book::setClose( ) {
	setAnim( ANIM_CLOSING );
}

void Book::setOpen( ) {
	setAnim( ANIM_OPENING );
}

Vector Book::getSize( ) const {
	return _book_left->getOriginMeterSize( );
}

void Book::setAnim( ANIM anim ) {
	_anim = anim;
	_time = 0;
}

int Book::getDeltaMilliTime( ) const {
	return Manager::getInstance( )->getDeltaMilliTime( );
}