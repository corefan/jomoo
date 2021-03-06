

#ifndef _Connection_H_
#define _Connection_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jomoo/db/config_db.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"

_jomoo_db_begin

enum DBType
{
	DB_UNKOWN,
	DB_TEXT,
	DB_INTEGER_8,
	DB_INTEGER_16,
	DB_INTEGER_32,
	DB_INTEGER_64,
	DB_DOUBLE,
	DB_TIMESTAMP,
	DB_TIMESPAN,
	DB_BLOB,
	DB_NULL
};

enum DB_ERROR
{
	DB_OK = 0,
	DB_INSUFFICIENT = -1, /* 数据buf不足 */
	DB_INTERNAL = -2,	  /* 数据库内部错误 */
	DB_MISMATCH  = -3,     /* 数据内型不匹配 */
	DB_NOTFOUND  = -4     /* 列没有找到 */
};

struct columnItem
{
	DBType columnType;
	tstring columnName;
};

/**
 * 指定连接的事务锁定行为。
 */
enum IsolationLevel
{
 // 无法改写隔离级别更高的事务中的挂起的更改。 
 Chaos,
 // 在正在读取数据时保持共享锁，以避免脏读，但是在事务结束之前可以更改数据，从而导致不可重复的读取或幻像数据。  
 ReadCommitted,
 // 可以进行脏读，意思是说，不发布共享锁，也不接受独占锁。  
 ReadUncommitted,
 // 在查询中使用的所有数据上放置锁，以防止其他用户更新这些数据。防止不可重复的读取，但是仍可以有幻像行。  
 RepeatableRead,
 // 在 DataSet 上放置范围锁，以防止在事务完成之前由其他用户更新行或向数据集中插入行。  
 Serializable,
 // 通过在一个应用程序正在修改数据时存储另一个应用程序可以读取的相同数据版本来减少阻止。表示您无法从一个事务中看到在其他事务中进行的更改，即便重新查询也是如此。
 Snapshot,
 // 正在使用与指定隔离级别不同的隔离级别，但是无法确定该级别。 
 // 当使用 OdbcTransaction 时，如果不设置 IsolationLevel 或者将 IsolationLevel 设置为 Unspecied，事务将根据基础 ODBC 驱动程序的默认隔离级别来执行。
 Unspecified
};

MakeException( DbException , _T("数据库操作发生错误!") );

namespace spi
{

class transaction;
class query;
class command;

class connection : public jomoo_shared
{
public:
	virtual ~connection() {}

	/**
	 * 创建一个数据库连接
	 * @param[ in ] parameters 连接参数,一般是dsn字符串
	 * @param[ in ] len 连接参数字符串的长度,默认为-1表示不知有多长
	 */
	virtual bool open(const tchar* parameters, size_t len ) = 0;

	/**
	 * 关闭数据库连接
	 */
	virtual void close() = 0;

	/**
	 * 使用另一个数据库
	 * @param[ in ] database 数据库名字
	 * @param[ in ] len 数据库名字字符串的长度,默认为-1表示不知有多长
	 */
	virtual bool uses(const tchar* database, size_t len ) = 0;

	/**
	 * 创建一个查询对象
	 */
	virtual query* createQuery() = 0;

	/**
	 * 创建一个执行对象
	 */
	virtual command* createCommand() = 0;

	/**
	 * 开始一个事务
	 */
	virtual transaction* beginTransaction( IsolationLevel level )    = 0;

	/**
	 * 取得最后一次错误
	 */
	virtual const tstring& last_error() const = 0;

	/**
	 * 数据库连接名
	 */
	virtual const tstring& name() const = 0;
};

}

_jomoo_db_end

#endif // _Connection_H_
