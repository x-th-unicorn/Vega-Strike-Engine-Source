#ifndef VSNET_SOCKETSET_H
#define VSNET_SOCKETSET_H

#include <config.h>

/* 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*
  netUI - Network Interface - written by Stephane Vaxelaire <svax@free.fr>
*/

#include <iostream>
#include <errno.h>
#if defined(_WIN32) && !defined(__CYGWIN__)
	//#warning "Win32 platform"
	#define in_addr_t unsigned long
	#include <winsock.h>
#else
	#include <sys/socket.h>
	#include <sys/time.h>
#endif

class SocketSet
{
    fd_set _set;
    int    _max_sock;
public:
    SocketSet( ) : _max_sock( 0 )
    {
	clear();
    }

    inline void set( int fd ) {
	FD_SET( fd, &_set);
		if( fd >= _max_sock ) _max_sock = fd+1;
    }
    inline bool isset( int fd ) const { return FD_ISSET( fd, &_set); }
    inline void clear( ) { FD_ZERO( &_set ); }

    int select( timeval* timeout );

private:
    SocketSet( const SocketSet& ); // forbidden copy constructor
    SocketSet& operator=( const SocketSet& ); // forbidden assignment operator
};

#endif /* VSNET_SOCKETSET_H */

