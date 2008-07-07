
/* Copyright (c) 2008, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#ifndef EQSERVER_COMPOUND_LISTENER_H
#define EQSERVER_COMPOUND_LISTENER_H

#include <eq/base/base.h>

namespace eq
{
namespace server
{
    class Compound;

    /** A listener on various compound operations. */
    class CompoundListener
    {
    public:
        virtual ~CompoundListener(){}

        /** 
         * Notify that the compound tree below and including compound is about
         * to be updated.
         *
         * Called on each compound of the tree during update.
         *
         * @param compound the root compound of the tree to be updated.
         * @param frameNumber the new frame number.
         */
        virtual void notifyUpdatePre( Compound* compound, 
                                      const uint32_t frameNumber ) {}
    };
}
}
#endif // EQSERVER_COMPOUND_LISTENER_H
