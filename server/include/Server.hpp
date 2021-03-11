/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP_
# define SERVER_HPP_

#include "AServer.hpp"
#include "Handler.hpp"

#include <boost/asio/signal_set.hpp>

#include <algorithm>
#include <chrono>
#include <thread>

# define DEFAULT_PORT 8080

namespace server
{
    namespace asio
    {
        class AsioServer : public AServer<tcp::socket, Handler>
        {
            public:
                AsioServer(const char **av);
                ~AsioServer() = default;
            public:
                void run() final;
            private:
                void loop();
                void waitEndSignal();
                void waitEvent() final;
                void accept();
                void deconnect();
                void handleClient(tcp::socket socket) final;
                void updClient();
            private:
                io_context    _context;
                signal_set    _signals;
                tcp::acceptor _acceptor;
                bool          _stop;
        };
    }
}

using namespace server::asio;

#endif /* !SERVER_HPP_ */
