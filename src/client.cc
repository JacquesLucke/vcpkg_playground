#include <fmt/format.h>
#include <zmq.hpp>

int main() {
  zmq::context_t ctx;
  zmq::socket_t socket(ctx, zmq::socket_type::req);
  const std::string endpoint = "ipc:///tmp/server.ipc";
  socket.connect(endpoint);

  fmt::print("Connected to server at {}\n", endpoint);

  for (int i = 0; i < 10; i++) {
    socket.send(zmq::buffer(fmt::format("Hey {}", i)), zmq::send_flags::none);

    zmq::message_t reply;
    zmq::recv_result_t res = socket.recv(reply, zmq::recv_flags::none);
    if (!res) {
      continue;
    }
    fmt::print("Received reply: {}\n", reply.to_string_view());
  }
  return 0;
}