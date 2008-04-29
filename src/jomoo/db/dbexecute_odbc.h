#ifndef _DbExecute_ODBC_h_
#define _DbExecute_ODBC_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "DbExecute.h"
# include <sql.h>

_jomoo_db_begin

class DbConnection_ODBC;

class DbExecute_ODBC : public DbExecute2
{
public:
	DbExecute_ODBC( DbConnection_ODBC* con , int timeout = 120 );
	~DbExecute_ODBC();

	bool direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors );
	bool direct_exec( const tstring& sql, bool reportWarningsAsErrors );
	bool prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors = true );
	bool prepare( const tstring& sql, bool reportWarningsAsErrors = true );
	bool exec( );
	bool reset( );
	int affected_rows( );

	bool bind( int index, int value );
	bool bind( int index, __int64 value );
	bool bind( int index, double value );
	bool bind( int index, const char* str , size_t n);
	bool bind( int index, const wchar_t* str , size_t n );
	bool bind( int index, const Timestamp& time );

	bool bind( const tstring& name, int value );
	bool bind( const tstring& name, __int64 value );
	bool bind( const tstring& name, double value );
	bool bind( const tstring& name, const char* str , size_t n );
	bool bind( const tstring& name, const wchar_t* str , size_t n );
	bool bind( const tstring& name, const Timestamp& time );

	bool bind( const tchar* name, size_t len, int value );
	bool bind( const tchar* name, size_t len, __int64 value );
	bool bind( const tchar* name, size_t len, double value );
	bool bind( const tchar* name, size_t len, const char* str , size_t n );
	bool bind( const tchar* name, size_t len, const wchar_t* str , size_t n );
	bool bind( const tchar* name, size_t len, const Timestamp& time );


	DECLARE_SHARED( );
private:
	
	void reportError_( const tstring& message );

	DbConnection_ODBC *con_;
	//
	SQLHSTMT   stmt_;

	SQLCHAR    *sqlText_;
	SQLSMALLINT sqlTextSize_;

	// error handling
	bool reportWarningsAsErrors_;
};


_jomoo_db_end

#endif // _DbExecute_ODBC_h_