
#ifndef __TRANSACTION__
#define __TRANSACTION__

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "IConnection.h"

_jomoo_db_begin

class ITransaction : jomoo_shared
{
public:
	virtual ~IDbTransaction() {}

	/**
	 * ������ݿ����Ӷ���
	 * @remarks ���õ����ݿ����Ӷ���ָ����������ڲ��ɳ���������
	 */
    virtual IConnection* connection() = 0;

	/**
	 * ȡ�õ������ IsolationLevel
	 */
	virtual IsolationLevel level() const = 0;

	/**
	 * �ύ����
	 */
	virtual bool commit()   = 0;

	/**
	 * �ع�����
	 */
	virtual bool rollback() = 0;
};

_jomoo_db_end

#endif // __TRANSACTION__