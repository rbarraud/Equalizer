
/* Copyright (c) 2007-2009, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#ifndef EQ_EYE_H
#define EQ_EYE_H

#include <eq/base/debug.h>   // for EQABORT
#include <iostream>

namespace eq
{
    /**
     * Defines an eye pass.
     */
    enum Eye
    {
        EYE_CYCLOP = 0,
        EYE_LEFT,
        EYE_RIGHT,
        EYE_ALL   // must be last
    };

    inline std::ostream& operator << ( std::ostream& os, const Eye& eye )
    {
        switch( eye )
        {
            case EYE_LEFT: 
                os << "left eye";
                break;
            case EYE_RIGHT: 
                os << "right eye";
                break;
            case EYE_CYCLOP: 
                os << "cyclop eye";
                break;
            case EYE_ALL: 
            default: 
                EQABORT( "Invalid eye value" );
        }

        return os;
    }
}

#endif // EQ_EYE_H
