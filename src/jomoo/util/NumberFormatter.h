
#ifndef _NumberFormatter_H_
#define _NumberFormatter_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>

#if defined(_MSC_VER)
	#define I64_FMT _T("I64")
#elif defined(__APPLE__)
	#define I64_FMT _T("q")
#else
	#define I64_FMT _T("ll")
#endif

_jomoo_begin


class NumberFormatter
{
public:

	static void sprintf( tstring& buffer,const tchar* fmt, ... )
	{
		va_list argptr;
		va_start(argptr,fmt );
#ifdef __GNUG__
#ifdef  _UNICODE
		buffer.resize( _vsnwprintf(( tchar*) buffer.c_str(), buffer.size(), fmt, argptr ) );
#else
		buffer.resize( vsnprintf(( tchar*) buffer.c_str(), buffer.size(), fmt, argptr ) );
#endif
#else
#ifdef  _UNICODE
		buffer.resize( _vsnwprintf_s(( tchar*) buffer.c_str(), buffer.capacity( ), buffer.size(), fmt, argptr ) );
#else
		buffer.resize( vsnprintf_s(( tchar*) buffer.c_str(), buffer.capacity( ), buffer.size(), fmt, argptr ) );
#endif
#endif
		va_end(argptr);
	}

	static tstring format(int value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%d"), value);
		return buffer;
	}

	static tstring format(int value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%*d"), width, value);
		return buffer;
	}

	static tstring format0(int value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*d"), width, value);
		return buffer;
	}

	static tstring formatHex(int value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%X"), value);
		return buffer;
	}

	static tstring formatHex(int value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*X"), width, value);
		return buffer;
	}

	static tstring format(unsigned value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%u"), value);
		return buffer;
	}

	static tstring format(unsigned value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%*u"), width, value);
		return buffer;
	}

	static tstring format0(unsigned int value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*u"), width, value);
		return buffer;
	}


	static tstring formatHex(unsigned value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%X"), value);
		return buffer;
	}

	static tstring formatHex(unsigned value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*X"), width, value);
		return buffer;
	}

	static tstring format(long value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%ld"), value);
		return buffer;
	}

	static tstring format(long value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%*ld"), width, value);
		return buffer;
	}

	static tstring format0(long value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*ld"), width, value);
		return buffer;
	}

	static tstring formatHex(long value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%lX"), value);
		return buffer;
	}

	static tstring formatHex(long value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*lX"), width, value);
		return buffer;
	}

	static tstring format(unsigned long value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%lu"), value);
		return buffer;
	}

	static tstring format(unsigned long value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%*lu"), width, value);
		return buffer;
	}

	static tstring format0(unsigned long value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*lu"), width, value);
		return buffer;
	}

	static tstring formatHex(unsigned long value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%lX"), value);
		return buffer;
	}

	static tstring formatHex(unsigned long value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*lX"), width, value);
		return buffer;
	}

	static tstring format(int64_t value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%") I64_FMT _T("d"), value);
		return buffer;
	}

	static tstring format(int64_t value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%*") I64_FMT _T("d"), width, value);
		return buffer;
	}

	static tstring format0(int64_t value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*") I64_FMT _T("d"), width, value);
		return buffer;
	}

	static tstring formatHex(int64_t value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%") I64_FMT _T("X"), value);
		return buffer;
	}

	static tstring formatHex(int64_t value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*") I64_FMT _T("X"), width, value);
		return buffer;
	}

	static tstring format(u_int64_t value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%") I64_FMT _T("u"), value);
		return buffer;
	}

	static tstring format(u_int64_t value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%*") I64_FMT _T("u"), width, value);
		return buffer;
	}

	static tstring format0(u_int64_t value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*") I64_FMT _T("u"), width, value);
		return buffer;
	}

	static tstring formatHex(u_int64_t value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%") I64_FMT _T("X"), value);
		return buffer;
	}

	static tstring formatHex(u_int64_t value, int width)
	{
		tstring buffer;
		buffer.resize( width + 10 );

		sprintf(buffer, _T("%0*") I64_FMT _T("X"), width, value);
		return buffer;
	}

	static tstring format(float value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%.*g"), 10, (double) value);
		return buffer;
	}

	static tstring format(double value)
	{
		tstring buffer;
		buffer.resize( 64 );

		sprintf(buffer, _T("%.*g"), 20, value);
		return buffer;
	}

	static tstring format(double value, int precision)
	{
		tstring buffer;
		buffer.resize( 2*precision + 10 );

		sprintf(buffer, _T("%.*f"), precision, value);
		return buffer;
	}


	static tstring format(double value, int width, int precision)
	{
		tstring buffer;
		buffer.resize( 2*((width > precision) ? width : precision) + 10 );

		sprintf(buffer, _T("%*.*f"), width, precision, value);
		return buffer;
	}

	static tstring format(const void* ptr)
	{
		tstring buffer;
		buffer.resize( 64 );

		//string_traits<tstring::value_type>::sp
		sprintf(buffer, _T("%08lX"), (int) ptr);
		return buffer;
	}
};


_jomoo_end


#endif // _NumberFormatter_H_
