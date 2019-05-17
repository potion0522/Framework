#pragma once
#include <vector>
#include <string>


/*******************************************

	CSV�f�[�^�̓ǂݍ��ݗp�̍\����
	�ҏW�͂ł��Ȃ��B�ǂݎ���p

*******************************************/
struct CsvData {
	// �G�f�B�^�[����A�N�Z�X�\�ɂ���
	friend struct CsvEditor;

public:
	enum RESULT {
		RESULT_SUCCESS,
		RESULT_ERROR_FILEOPEN
	};

private:
	typedef std::string CELL;			// �Z��
	typedef std::vector< CELL > COLUMN;	// ��(1�s��)
	std::vector< COLUMN > _data;
	const char* PATH;

public:
	// init
	/***************************************************************/
	CsvData( ) {
	}
	~CsvData( ) {
	}

	CsvData( const char* path, RESULT* result = NULL ) :
	PATH( path ) {
		FILE* fp;
		if ( fopen_s( &fp, PATH, "rb" ) != 0 ) {
			if ( result != NULL ) {
				*result = RESULT_ERROR_FILEOPEN;
			}

			return;
		}

		CELL cell;
		COLUMN colmun;
		char c;

		do {
			c = fgetc( fp );

			switch ( c ) {
			case ',':	// �Z����؂�
				colmun.push_back( cell );
				cell.clear( );
				break;

			case '\r':	// ����
				break;

			case '\n':	// ���s
			case EOF :
				if ( !cell.empty( )   ) colmun.push_back( cell );
				if ( !colmun.empty( ) ) _data.push_back( colmun );
				colmun.clear( );
				cell.clear( );
				break;

			default:	// ����
				cell += c;
				break;
			}

		} while ( c != EOF );

		fclose( fp );

		if ( result != NULL ) {
			*result = RESULT_SUCCESS;
		}
	}


	// getter
	/***************************************************************/
	inline int getMaxRow( ) const {
		return ( int )_data.size( );
	}
	inline int getMaxCol( const int& row ) const {
		return ( int )_data[ row ].size( );
	}
	inline std::string getCell( const int& row, const int& col ) const {
		return _data[ row ][ col ];
	}
	inline std::string getFilePath( ) const {
		return PATH;
	}
};








/*******************************************************

	CSV�̕ҏW�p�̍\����
	�����̂���,�V�K�����Ƃ��ҏW�E�G�N�X�|�[�g�\

*******************************************************/
struct CsvEditor {
public:
	enum INDEX_OVER_RANGE {
		INDEX_OVER_RANGE_INSERT_BLANK,
		INDEX_OVER_RANGE_NO_ACTION,
	};
	enum EXPORT_RESULT {
		EXPORT_SUCCESS,        // ����
		EXPORT_ERROR_FILEOPEN, // fopen_s�Ɏ��s
	};

private:
	enum EDIT_TYPE {
		EDIT_TYPE_CREATE_NEW_FILE,
		EDIT_TYPE_EXISTING,
	};

private:
	CsvData* _edit_data;
	INDEX_OVER_RANGE _over_range_type;
	EDIT_TYPE _edit_type;
	const char* EXPORT_PATH;

public:
	// init
	/***************************************************************/

	// �V�����t�@�C���𐶐�
	CsvEditor( const char* export_path ) : 
	_over_range_type( INDEX_OVER_RANGE_INSERT_BLANK ),
	_edit_type( EDIT_TYPE_CREATE_NEW_FILE ),
	EXPORT_PATH( export_path ) {
		_edit_data = new CsvData;
	}

	// �����̃t�@�C����ҏW
	CsvEditor( CsvData* data ) : 
	_edit_data( data ),
	_over_range_type( INDEX_OVER_RANGE_INSERT_BLANK ),
	_edit_type( EDIT_TYPE_EXISTING ),
	EXPORT_PATH( _edit_data->PATH ) {
	}

	~CsvEditor( ) {
		if ( _edit_type == EDIT_TYPE_CREATE_NEW_FILE ) {
			delete _edit_data;
		}
	}

public:
	/***************************************************************/

	// �ҏW����Z���̗v�f�I�[�o�[�ɑ΂��鏈��
	inline void settingIndexOverRangeType( INDEX_OVER_RANGE type ) { 
		_over_range_type = type;
	}

	// �Ώۂ̃Z����ҏW
	inline void editCell( const int& row, const int& col, const char* word ) { 
		// index ���I�[�o�[���Ă�����
		if ( _edit_data->getMaxRow( ) <= row || _edit_data->getMaxCol( row ) <= col ) {
			actOnIndexOver( row, col );
			if ( _over_range_type == INDEX_OVER_RANGE_NO_ACTION ) return;
		}

		_edit_data->_data[ row ][ col ] = word;
	}

	inline EXPORT_RESULT exportCsv( ) { // ���݂̃f�[�^�������o��
		FILE* fp;
		if ( fopen_s( &fp, EXPORT_PATH, "wb" ) != 0 ) {
			// ERROR
			return EXPORT_ERROR_FILEOPEN;
		}
		
		// �����o��
		for ( int i = 0; i < _edit_data->getMaxRow( ); i++ ) {
			for ( int j = 0; j < _edit_data->getMaxCol( i ); j++ ) {
				fprintf_s( fp, "%s,", _edit_data->getCell( i, j ).c_str( ) );
			}
			fprintf_s( fp, "\r\n" );
		}

		fclose( fp );

		return EXPORT_SUCCESS;
	}

private:
	/***************************************************************/
	inline void actOnIndexOver( const int& row, const int& col ) {
		switch ( _over_range_type ) {
		case INDEX_OVER_RANGE_INSERT_BLANK: // ����Ȃ������󔒂ŕۊ�
			actOnInsertBlank( row, col );
			break;

		case INDEX_OVER_RANGE_NO_ACTION: // �������Ȃ�
			break;
		}
	}
	inline void actOnInsertBlank( const int& row, const int& col ) {
		// row
		int over_row = row - ( _edit_data->getMaxRow( ) - 1 );
		for ( int i = 0; i < over_row; i++ ) addRow( );

		// col
		int over_col = col - ( _edit_data->getMaxCol( row ) - 1 );
		for ( int i = 0; i < over_col; i++ ) addCol( row );
	}


	inline void addRow( ) {
		_edit_data->_data.push_back( CsvData::COLUMN( ) );
	}
	inline void addCol( const int& row ) {
		_edit_data->_data[ row ].push_back( CsvData::CELL( ) );
	}
};