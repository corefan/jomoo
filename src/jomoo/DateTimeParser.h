# ifndef DateTimeParser_H
# define DateTimeFormatter_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
#include "Poco/DateTime.h"


namespace Poco {


class Foundation_API DateTimeParser
	/// This class provides a method for parsing dates and times
	/// from strings. All parsing methods do their best to
	/// parse a meaningful result, even from malformed input
	/// strings.
	///
	/// The returned DateTime will always contain a time in the same
	/// timezone as the time in the string. Call DateTime::makeUTC()
	/// with the timeZoneDifferential returned by parse() to convert
	/// the DateTime to UTC.
	///
	/// Note: When parsing a time in 12-hour (AM/PM) format, the hour
	/// (%h) must be parsed before the AM/PM designator (%a, %A),
	/// otherwise the AM/PM designator will be ignored.
{
public:
	static void parse(const std::string& fmt, const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
		/// Parses a date and time in the given format from the given string.
		/// Throws a SyntaxException if the string cannot be successfully parsed.
		/// Please see DateTimeFormatter::format() for a description of the format string.
		/// Class DateTimeFormat defines format strings for various standard date/time formats.

	static DateTime parse(const std::string& fmt, const std::string& str, int& timeZoneDifferential);
		/// Parses a date and time in the given format from the given string.
		/// Throws a SyntaxException if the string cannot be successfully parsed.
		/// Please see DateTimeFormatter::format() for a description of the format string.
		/// Class DateTimeFormat defines format strings for various standard date/time formats.
		
	static bool tryParse(const std::string& fmt, const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
		/// Parses a date and time in the given format from the given string.
		/// Returns true if the string has been successfully parsed, false otherwise.
		/// Please see DateTimeFormatter::format() for a description of the format string.
		/// Class DateTimeFormat defines format strings for various standard date/time formats.
		
	static void parse(const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
		/// Parses a date and time from the given dateTime string. Before parsing, the method
		/// examines the dateTime string for a known date/time format.
		/// Throws a SyntaxException if the string cannot be successfully parsed.
		/// Please see DateTimeFormatter::format() for a description of the format string.
		/// Class DateTimeFormat defines format strings for various standard date/time formats.

	static DateTime parse(const std::string& str, int& timeZoneDifferential);
		/// Parses a date and time from the given dateTime string. Before parsing, the method
		/// examines the dateTime string for a known date/time format.
		/// Please see DateTimeFormatter::format() for a description of the format string.
		/// Class DateTimeFormat defines format strings for various standard date/time formats.
		
	static bool tryParse(const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
		/// Parses a date and time from the given dateTime string. Before parsing, the method
		/// examines the dateTime string for a known date/time format.
		/// Please see DateTimeFormatter::format() for a description of the format string.
		/// Class DateTimeFormat defines format strings for various standard date/time formats.

	static int parseMonth(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Tries to interpret the given range as a month name. The range must be at least
		/// three characters long. 
		/// Returns the month number (1 .. 12) if the month name is valid. Otherwise throws
		/// a SyntaxException.

	static int parseDayOfWeek(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Tries to interpret the given range as a weekday name. The range must be at least
		/// three characters long. 
		/// Returns the weekday number (0 .. 6, where 0 = Synday, 1 = Monday, etc.) if the 
		/// weekday name is valid. Otherwise throws a SyntaxException.
		
protected:
	static int parseTZD(std::string::const_iterator& it, const std::string::const_iterator& end);
	static int parseAMPM(std::string::const_iterator& it, const std::string::const_iterator& end, int hour);
};


} // namespace Poco


#endif // Foundation_DateTimeParser_INCLUDED
