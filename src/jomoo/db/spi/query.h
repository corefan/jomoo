
#ifndef _Query_H_
#define _Query_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jomoo/db/config_db.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"
# include "connection.h"

_jomoo_db_begin

namespace spi
{

class query : public jomoo_shared
{
public:
	virtual ~query() {}

	/**
	 * 执行sql语句
	 * @param[ in ] sql sql语句
	 * @param[ in ] len sql语句的长度,默认为-1表示不知道有多长
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	virtual bool exec(const tchar* sql, size_t len, bool reportWarningsAsErrors ) = 0;

	/**
	 * 切换到下一个记录
	 */
	virtual bool nextRow() = 0;

	/**
	 * 切换到下一记录集
	 */
	virtual bool nextSet() = 0;

	/**
	 * 取得当前结果共有多少列
	 */
	virtual size_t columns() const = 0;

	/**
	 * 取得指定列的数据类型,请见枚举 DBType
	 * @see DBType
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual int columnType( size_t pos ) const = 0;

	/**
	 * 取得指定列的列名
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual const tchar* columnName( size_t pos ) const = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, bool& value) = 0;

	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, bool& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, int8_t& value) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, int8_t& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, int16_t& value) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, int16_t& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, int32_t& value) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, int32_t& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, int64_t& value) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, int64_t& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, Timestamp& value) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, Timestamp& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(u_int_t column, double& value) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 */
	virtual bool read(const tchar* columnName, double& value) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] buf 数据buf
	 * @param[ in,out ] len buf的长度,在成功或发生DB_INSUFFICIENT错误时返回读取的长度
	 * @return 成功返回DB_OK
	 * @see DB_ERROR
	 */
	virtual int read(u_int_t column, char* buf, size_t& len ) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] buf 数据buf
	 * @param[ in,out ] len buf的长度,在成功或发生DB_INSUFFICIENT错误时返回读取的长度
	 * @return 成功返回DB_OK
	 * @see DB_ERROR
	 */
	virtual int read(const tchar* columnName, char* buf, size_t& len ) = 0;

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] buf 数据buf
	 * @param[ in,out ] len buf的长度,在成功或发生DB_INSUFFICIENT错误时返回读取的长度
	 * @return 成功返回DB_OK
	 * @see DB_ERROR
	 */
	virtual int readBLOB(u_int_t column, void* buf, size_t& len ) = 0;
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] buf 数据buf
	 * @param[ in,out ] len buf的长度,在成功或发生DB_INSUFFICIENT错误时返回读取的长度
	 * @return 成功返回DB_OK
	 * @see DB_ERROR
	 */
	virtual int readBLOB(const tchar* columnName, void* buf, size_t& len ) = 0;

	/**
	 * 当列为DB_TEXT和DB_BLOB时,从当前记录中读取指定列的数据长度,否则返回错误
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] len 数据长度
	 */
	virtual bool readLength(u_int_t column, size_t& len ) = 0;
	/**
	 * 当列为DB_TEXT和DB_BLOB时,从当前记录中读取指定列的数据长度,否则返回错误
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] len 数据长度
	 */
	virtual bool readLength(const tchar* columnName, size_t& len ) = 0;
};

}

_jomoo_db_end

#endif // _Query_H_
