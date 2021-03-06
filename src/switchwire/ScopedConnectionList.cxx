/*************** <auto-copyright.rb BEGIN do not edit this line> **************
 *
 * Copyright 2012-2012 by Ames Laboratory
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.rb END do not edit this line> ***************/
#include <switchwire/ScopedConnectionList.h>


namespace switchwire
{
struct null_deleter
{
    void operator()(void*) {}
};

ScopedConnectionList::ScopedConnectionList()
{
    this_ = boost::shared_ptr< ScopedConnectionList >( this, null_deleter() );
}

ScopedConnectionList::ScopedConnectionList( const ScopedConnectionList& )
{
    this_ = boost::shared_ptr< ScopedConnectionList >( this, null_deleter() );
}

ScopedConnectionList::~ScopedConnectionList( )
{
}

void ScopedConnectionList::AddConnection( boost::shared_ptr< boost::signals2::scoped_connection > connection )
{
    mConnections.push_back( connection );
}

void ScopedConnectionList::DropConnections( )
{
    // Since shared pointers automatically delete when they go out of scope,
    // we can simply clear the list to cause the connections to autodelete
    mConnections.clear( );
}

ScopedConnectionList::ConnectionList_type::iterator ScopedConnectionList::GetBegin( )
{
    return mConnections.begin();
}

ScopedConnectionList::ConnectionList_type::iterator ScopedConnectionList::GetEnd( )
{
    return mConnections.end();
}

boost::shared_ptr< boost::signals2::scoped_connection > ScopedConnectionList::GetLastConnection( )
{
    ConnectionList_type::iterator iter = mConnections.end( );
    if( iter != mConnections.begin( ) )
    {
        iter--; // Decrement because mConnections.end() returns one position *past* the last element
        return (*iter );
    }
    else
    {
        // If there are no existing connections, return an empty one.
        boost::shared_ptr< boost::signals2::scoped_connection > emptyConnection( new boost::signals2::scoped_connection );
        return emptyConnection;
    }
}

}

