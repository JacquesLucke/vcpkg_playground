#include <fmt/format.h>
#include <zmq.hpp>

int main() {
  zmq::context_t ctx;
  zmq::socket_t socket(ctx, zmq::socket_type::req);
  const std::string endpoint = "ipc:///tmp/server.ipc";
  socket.connect(endpoint);

  fmt::print("Connected to server at {}\n", endpoint);

  socket.send(zmq::str_buffer("Hey"), zmq::send_flags::none);

  zmq::message_t reply;
  zmq::recv_result_t res = socket.recv(reply, zmq::recv_flags::none);
  std::string reply_str{static_cast<char *>(reply.data()), reply.size()};
  fmt::print("Received reply: {}\n", reply_str);
  return 0;
}