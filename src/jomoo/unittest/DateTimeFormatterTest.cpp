

#include "stdafx.h"
#include "DateTimeFormatterTest.h"
#include "marco.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "jomoo/DateTimeFormatter.h"
#include "jomoo/DateTime.h"
#include "jomoo/Timespan.h"



CPPUNIT_TEST_SUITE_REGISTRATION( DateTimeFormatterTest );



void DateTimeFormatterTest::testISO8601()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::ISO8601_FORMAT);
	CPPUNIT_ASSERT (str == "2005-01-08T12:30:00Z");

	str = DateTimeFormatter::format(dt, DateTime::ISO8601_FORMAT, 3600);
	CPPUNIT_ASSERT (str == "2005-01-08T12:30:00+01:00");

	str = DateTimeFormatter::format(dt, DateTime::ISO8601_FORMAT, -3600);
	CPPUNIT_ASSERT (str == "2005-01-08T12:30:00-01:00");
}


void DateTimeFormatterTest::testRFC822()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::RFC822_FORMAT);
	CPPUNIT_ASSERT (str == "Sat, 8 Jan 05 12:30:00 GMT");

	str = DateTimeFormatter::format(dt, DateTime::RFC822_FORMAT, 3600);
	CPPUNIT_ASSERT (str == "Sat, 8 Jan 05 12:30:00 +0100");

	str = DateTimeFormatter::format(dt, DateTime::RFC822_FORMAT, -3600);
	CPPUNIT_ASSERT (str == "Sat, 8 Jan 05 12:30:00 -0100");
}


void DateTimeFormatterTest::testRFC1123()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::RFC1123_FORMAT);
	CPPUNIT_ASSERT (str == "Sat, 8 Jan 2005 12:30:00 GMT");

	str = DateTimeFormatter::format(dt, DateTime::RFC1123_FORMAT, 3600);
	CPPUNIT_ASSERT (str == "Sat, 8 Jan 2005 12:30:00 +0100");

	str = DateTimeFormatter::format(dt, DateTime::RFC1123_FORMAT, -3600);
	CPPUNIT_ASSERT (str == "Sat, 8 Jan 2005 12:30:00 -0100");
}


void DateTimeFormatterTest::testHTTP()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::HTTP_FORMAT);
	CPPUNIT_ASSERT (str == "Sat, 08 Jan 2005 12:30:00 GMT");

	str = DateTimeFormatter::format(dt, DateTime::HTTP_FORMAT, 3600);
	CPPUNIT_ASSERT (str == "Sat, 08 Jan 2005 12:30:00 +0100");

	str = DateTimeFormatter::format(dt, DateTime::HTTP_FORMAT, -3600);
	CPPUNIT_ASSERT (str == "Sat, 08 Jan 2005 12:30:00 -0100");
}


void DateTimeFormatterTest::testRFC850()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::RFC850_FORMAT);
	CPPUNIT_ASSERT (str == "Saturday, 8-Jan-05 12:30:00 GMT");

	str = DateTimeFormatter::format(dt, DateTime::RFC850_FORMAT, 3600);
	CPPUNIT_ASSERT (str == "Saturday, 8-Jan-05 12:30:00 +0100");

	str = DateTimeFormatter::format(dt, DateTime::RFC850_FORMAT, -3600);
	CPPUNIT_ASSERT (str == "Saturday, 8-Jan-05 12:30:00 -0100");
}


void DateTimeFormatterTest::testRFC1036()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::RFC1036_FORMAT);
	CPPUNIT_ASSERT (str == "Saturday, 8 Jan 05 12:30:00 GMT");

	str = DateTimeFormatter::format(dt, DateTime::RFC1036_FORMAT, 3600);
	CPPUNIT_ASSERT (str == "Saturday, 8 Jan 05 12:30:00 +0100");

	str = DateTimeFormatter::format(dt, DateTime::RFC1036_FORMAT, -3600);
	CPPUNIT_ASSERT (str == "Saturday, 8 Jan 05 12:30:00 -0100");
}


void DateTimeFormatterTest::testASCTIME()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::ASCTIME_FORMAT);
	CPPUNIT_ASSERT (str == "Sat Jan  8 12:30:00 2005");
}


void DateTimeFormatterTest::testSORTABLE()
{
	DateTime dt(2005, 1, 8, 12, 30, 00);

	std::string str = DateTimeFormatter::format(dt, DateTime::SORTABLE_FORMAT);
	CPPUNIT_ASSERT (str == "2005-01-08 12:30:00");
}


void DateTimeFormatterTest::testCustom()
{
	DateTime dt(2005, 1, 8, 12, 30, 00, 250);

	std::string str = DateTimeFormatter::format(dt, "%w/%W/%b/%B/%d/%e/%f/%m/%n/%o/%y/%Y/%H/%h/%a/%A/%M/%S/%i/%c/%z/%Z/%%");
	CPPUNIT_ASSERT (str == "Sat/Saturday/Jan/January/08/8/ 8/01/1/ 1/05/2005/12/12/pm/PM/30/00/250/2/Z/GMT/%");
}


void DateTimeFormatterTest::testTimespan()
{
	Timespan ts(1, 1, 1, 1, 1000);
	std::string str = DateTimeFormatter::format(ts);
	CPPUNIT_ASSERT (str == "1d 01:01:01.001");

	Timespan ts1(1, 24, 1, 1, 1000);
	str = DateTimeFormatter::format(ts1);
	CPPUNIT_ASSERT (str == "2d 00:01:01.001");

	Timespan ts2(1, 25, 1, 1, 1000);
	str = DateTimeFormatter::format(ts2);
	CPPUNIT_ASSERT (str == "2d 01:01:01.001");

	Timespan ts3(5, 4, 3, 2, 1000);
	str = DateTimeFormatter::format(ts3, "%i.%S:%M:%H d%d %%");
	CPPUNIT_ASSERT (str == "001.02:03:04 d5 %");

	Timespan ts4(0, 24, 60, 60, 1001000);
	str = DateTimeFormatter::format(ts4);
	CPPUNIT_ASSERT (str == "1d 01:01:01.001");
	
	Timespan ts5(2, 11, 30, 20, 0);
	str = DateTimeFormatter::format(ts5, "%h %m %s");
	CPPUNIT_ASSERT (str == "59 3570 214220");
}


void DateTimeFormatterTest::setUp()
{
}


void DateTimeFormatterTest::tearDown()
{
}

