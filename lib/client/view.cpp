
/* Copyright (c) 2008-2009, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#include "view.h"

#include "viewVisitor.h"

#include <eq/net/dataIStream.h>
#include <eq/net/dataOStream.h>

namespace eq
{
View::View()
        : _layout( 0 )
{
}

View::~View()
{
    EQASSERT( !_layout );
    _layout = 0;
}

void View::serialize( net::DataOStream& os, const uint64_t dirtyBits )
{
    Frustum::serialize( os, dirtyBits );
    if( dirtyBits & DIRTY_VIEWPORT )
        os << _viewport;
}

void View::deserialize( net::DataIStream& is, const uint64_t dirtyBits )
{
    Frustum::deserialize( is, dirtyBits );
    if( dirtyBits & DIRTY_VIEWPORT )
        is >> _viewport;
}

const Viewport& View::getViewport() const
{
    return _viewport;
}

VisitorResult View::accept( ViewVisitor* visitor )
{
    return visitor->visit( this );
}

}
