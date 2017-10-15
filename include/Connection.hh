#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <array>
#include <memory>

#include "asio.hpp"

#include "ConnectionManager.hh"
#include "Reply.hh"
#include "Request.hh"

namespace http {
  class Connection : public std::enable_shared_from_this<Connection> {
  public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(ConnectionManager& connection_manager,
               asio::ip::tcp::socket socket);

    void start();
    void stop();

  private:
    void do_read();
    void do_write();

    Reply handle_request(const Request& request);

    ConnectionManager& connection_manager;
    asio::ip::tcp::socket socket;

    std::array<char, 8192> buffer;
    Reply reply;
  };
}

#endif /* _CONNECTION_H_ */
