#include <fmt/format.h>
#include <zmq.hpp>

#include "common.hh"

int main() {
  zmq::context_t ctx;
  zmq::socket_t socket(ctx, zmq::socket_type::req);
  const std::string endpoint = "ipc:///tmp/server.ipc";
  socket.connect(endpoint);

  fmt::print("Connected to server at {}\n", endpoint);

  for (int i = 0; i < 10; i++) {
    MyData data;
    data.name = "Alice";
    data.age = 42 + i;

    msgpack::sbuffer buffer;
    msgpack::pack(buffer, data);

    socket.send(zmq::buffer(std::string_view(buffer.data(), buffer.size())),
                zmq::send_flags::none);

    zmq::message_t reply;
    zmq::recv_result_t res = socket.recv(reply, zmq::recv_flags::none);
    if (!res) {
      continue;
    }
    fmt::print("Received reply: {}\n", reply.to_string_view());
  }
  return 0;
}