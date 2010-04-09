
/* Copyright (c) 2005-2010, Stefan Eilemann <eile@equalizergraphics.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef EQ_SERVER_H
#define EQ_SERVER_H

#include <eq/client/types.h>     // basic typedefs
#include <eq/fabric/nodeType.h>  // for NODETYPE_EQ_SERVER enum

#include <eq/net/node.h>         // base class

namespace eq
{
namespace fabric
{
template< class S, class C, class O, class L, class CV > class Config;
}
    class Client;
    class Config;
    class ConfigParams;

    /**
     * Proxy object for the connection to an Equalizer server.
     *
     * The server manages the configurations for a set of Equalizer
     * applications. This proxy object is used to connect to a server and obtain
     * and release a Config from the server.
     * @sa Client::connectServer
     */
    class Server : public net::Node
    {
    public:
        /** Construct a new server. */
        EQ_EXPORT Server();

        /** @name Internal */
        //@{
        void setClient( ClientPtr client );
        ClientPtr getClient(){ return _client; }

        EQ_EXPORT net::CommandQueue* getNodeThreadQueue();
        EQ_EXPORT net::CommandQueue* getCommandThreadQueue();
        //@}

        /** 
         * Choose a configuration on the server.
         * 
         * @param parameters the configuration parameters
         * @return The chosen config, or 0if no matching config was found.
         * @sa ConfigParams
         */
        EQ_EXPORT Config* chooseConfig( const ConfigParams& parameters );

        /** 
         * Release a configuration.
         * 
         * The passed configuration will be destroyed by this function and is no
         * longer valid after the call.
         *
         * @param config the configuration.
         */
        EQ_EXPORT void releaseConfig( Config* config );

        /** Undocumented - may not be supported in the future */
        EQ_EXPORT bool shutdown();
        
        /** @return the vector of configurations. */
        const ConfigVector& getConfigs() const { return _configs; }

    protected:
        /**
         * Destructs this server.
         */
        EQ_EXPORT virtual ~Server();

    private:
        /** The local client connected to the server */
        ClientPtr _client;
        friend class Client; // to call invokeCommand()

        /** The list of configurations. */
        ConfigVector _configs;

        /** Process-local server */
        bool _localServer;

        union // placeholder for binary-compatible changes
        {
            char dummy[64];
        };

        /** @sa net::Node::getType */
        virtual uint32_t getType() const { return fabric::NODETYPE_EQ_SERVER; }

        friend class fabric::Config< Server, Config, Observer, Layout, Canvas >;
        /**  Add a new config to this server. */
        void _addConfig( Config* config );

        /** Remove a config from this server. */
        bool _removeConfig( Config* config );

        /* The command handler functions. */
        net::CommandResult _cmdCreateConfig( net::Command& command );
        net::CommandResult _cmdDestroyConfig( net::Command& command );
        net::CommandResult _cmdChooseConfigReply( net::Command& command );
        net::CommandResult _cmdReleaseConfigReply( net::Command& command );
        net::CommandResult _cmdShutdownReply( net::Command& command );
    };

    inline std::ostream& operator << ( std::ostream& os, const Server* server )
    {
        if( !server )
        {
            os << "NULL server";
            return os;
        }

        os << "server " << (void*)server;
        return os;
    }
}

#endif // EQ_SERVER_H

