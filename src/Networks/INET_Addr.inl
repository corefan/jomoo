

JOMOO_INLINE
inet_address::inet_address (void)
{
	this->reset ();
}

JOMOO_INLINE
inet_address::inet_address (const char* address)
{
	this->reset ();
	this->set (address);
}

JOMOO_INLINE
inet_address::inet_address (const inet_address &sa)
{
	this->reset ();
	this->set (sa);
}

JOMOO_INLINE
inet_address::inet_address (u_short port_number,
							  const char* host_name )
{
	this->reset ();
	this->set (port_number,host_name );
}

JOMOO_INLINE
inet_address::inet_address (const char* port_number,
		const char* ip_addr )
{
	this->reset ();
	this->set (port_number,ip_addr );
}

JOMOO_INLINE
inet_address::inet_address (const sockaddr_in *addr, int len)
{
	this->reset ();
	this->set (addr, len);
}

JOMOO_INLINE
inet_address::inet_address (u_short port_number,
							  u_long inet_address)
{
	this->reset ();
	this->set (port_number, inet_address);
}

JOMOO_INLINE
inet_address::~inet_address (void)
{
}

JOMOO_INLINE
bool inet_address::operator != (const inet_address &sap) const
{
	return !((*this) == sap);
}

JOMOO_INLINE
bool inet_address::operator == (const inet_address &sap) const
{	return (::memcmp (&this->m_addr_,
		&sap.m_addr_,
		this->get_size ()) == 0);
}

JOMOO_INLINE
bool inet_address::operator < (const inet_address &rhs) const
{
  return (::memcmp (&this->m_addr_,
		&rhs.m_addr_,
		this->get_size ()) < 0 );
}

JOMOO_INLINE
bool inet_address::operator > (const inet_address &rhs) const
{
  return (::memcmp (&this->m_addr_,
		&rhs.m_addr_,
		this->get_size ()) > 0 );
}

JOMOO_INLINE void
inet_address::reset (void)
{
  memset (&this->m_addr_ , 0, sizeof (this->m_addr_ ));
  this->m_addr_.sa_family = AF_INET;
}

JOMOO_INLINE
void inet_address::set_port_number (u_short port_number,
									 bool encode )
{

	if (encode)
		port_number = htons (port_number);

	((sockaddr_in*) &m_addr_)->sin_port = port_number;
}

void inet_address::set_ip_address( u_long ip , bool encode )
{
	if (encode)
		ip = htonl ( ip );

	((sockaddr_in*) &m_addr_)->sin_addr.s_addr = ip;
}

u_long inet_address::get_ip_address ( void ) const
{
	return (((sockaddr_in*) &m_addr_)->sin_addr .s_addr);
}

u_short inet_address::get_port_number( void ) const 
{
	return htons( ((sockaddr_in*) &m_addr_)->sin_port );
}

int inet_address::addr_to_string (char* s,
							   size_t size ) const
{
	char* ipstr = inet_ntoa( ((sockaddr_in*) &m_addr_)->sin_addr );
	if( ipstr == 0 )
		return -1;
	size_t len = strlen( ipstr );
	if( size > len )
	{
		strcpy( s, ipstr );
		s += len;		
		size -= len;
	}
	char tmp[ 100 ] = "";
	itoa( get_port_number(), tmp, 10 );
	size_t lenp = strlen( tmp );
	if( size > ( lenp + 1 ) )
	{
		*s = ':';
		s ++;
		strcpy( s, tmp );
		return 0;
	}
	else
	{
		s[ 0 ] = 0;
		return -1;
	}
}


int inet_address::string_to_addr ( const char* address )
{
	return this->set( address );
}

int inet_address::set (const inet_address &sa)
{
	::memcpy( &this->m_addr_, &sa.m_addr_, sa.get_size () );
	return 0;
}
int inet_address::set (const char* address)
{
		if( strnicmp( address, "TCP://", sizeof( "TCP://") ) == 0 )
		address += 6;
	else if( strstr( address, "://" ) != 0 )
		return -1;

	std::vector< char > ip_addr( strlen( address ) + 10 , 0 );
	strcpy( &ip_addr[ 0 ], address );
	char *port_p = ::strrchr (&ip_addr[0], ':');

	if (port_p == 0) 
	{
		u_long ip = inet_addr( &ip_addr[0] );
		if( ip == INADDR_NONE )
			return -1;
		this->set_ip_address( ip );
		return 0;
	}
	else
	{
		*port_p = '\0'; ++port_p;
		return this->set (port_p, &ip_addr[0]);
	}
}


int inet_address::set (u_short port_number,
						u_long inet_address )
{
	this->set_ip_address ( inet_address );
	this->set_port_number ( port_number );
	return 0;
}


int inet_address::set (u_short port_number,
						const char* host_name )
{
	if (host_name == 0)
		return -1;

	this->reset();

	while( isspace( *host_name ) && (*host_name) ) host_name ++;

	u_long addr = inet_addr (host_name);
	if ( addr != INADDR_NONE )
	{
		this->set_ip_address ( addr );
		this->set_port_number ( port_number );
		return 0;
	}
	else
	{
		hostent *hp = ::gethostbyname( host_name );

		if (hp == 0)
			return -1;
		if( hp->h_length <= 0 )
			return -1;
		this->set_ip_address ( *( u_long* )hp->h_addr );
		this->set_port_number ( port_number );
		return 0;
	}
}

static int get_port_number_from_name (const char* port_name)
{
	int port_number = 0;
	char *endp = 0;
	port_number = static_cast < int>( strtol (port_name, &endp, 10));
	if (port_number > 0 && *endp == '\0')
	{
		return static_cast <u_short>( port_number);
	}
	return port_number;
}


int inet_address::set (const char* port_name,
						const char* host_name)
{
	int port_number = get_port_number_from_name (port_name);
	if (port_number < 0)
	{
		return (-1);
	}
	return this->set ( static_cast< u_short>( port_number),
		host_name );
}

int inet_address::set (const char* port_name,
						u_long inet_address )
{
	int port_number = get_port_number_from_name (port_name);
	if (port_number < 0)
	{
		return  (-1);
	}

	return this->set ( static_cast< u_short>( port_number),
		inet_address );
}

int inet_address::set (const sockaddr_in *addr, int len)
{
	::memcpy (&this->m_addr_, addr, len);
	return 0;
}

const tstring& inet_address::toString( ) const
{
	char ipstr[ 100 ] = "";
	addr_to_string( ipstr, 100 );
	to_string_ = ipstr;
	return to_string_;
}


size_t inet_address::get_size (void) const
{
	return sizeof( this->m_addr_ );
}

void inet_address::set_size (size_t size)
{
	
}

const void *inet_address::get_addr (void) const
{
	return &(this->m_addr_);
}

void *inet_address::get_addr (void)
{
	return &(this->m_addr_);
}

void inet_address::set_addr ( const void * addr, size_t len)
{
	if( len > get_size() )
		memcpy( get_addr(), addr, get_size() );
	else
		memcpy( get_addr(), addr, len );
}