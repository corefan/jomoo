
#ifndef _string_append_iterator_
#define _string_append_iterator_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

template <class _Container>
class string_append_iterator ITERATOR_BASE( input_iterator, tstring , ptrdiff_t )
{
protected:
	_Container* container;
public:
	typedef _Container          container_type;
	typedef void                value_type;
	typedef void                difference_type;
	typedef void                pointer;
	typedef void                reference;

	explicit string_append_iterator(_Container& __x) : container(&__x) {}
	string_append_iterator<_Container>&
		operator=(const typename _Container::value_type& ___value) {
			*container += ___value;
			return *this;
		}
		string_append_iterator<_Container>& operator*() { return *this; }
		string_append_iterator<_Container>& operator++() { return *this; }
		string_append_iterator<_Container>& operator++(int) { return *this; }
};


#endif // _string_append_iterator_