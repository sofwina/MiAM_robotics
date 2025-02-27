#ifndef NETORK_SERVER_SOCKET_HPP
#define NETORK_SERVER_SOCKET_HPP

#include <common/macros.hpp>
#include <network/socket.hpp>

namespace network {

//--------------------------------------------------------------------------------------------------
// Class declaration
//--------------------------------------------------------------------------------------------------

class ServerSocket : private Socket
{
 public:

  ServerSocket(int port);
  ServerSocket(){};
  virtual ~ServerSocket();

  ServerSocket const& operator << (std::string const&) const;
  ServerSocket const& operator >> (std::string&) const;

  void accept(ServerSocket&);

};

//--------------------------------------------------------------------------------------------------

} // namespace network

#endif // NETORK_SERVER_SOCKET_HPP
