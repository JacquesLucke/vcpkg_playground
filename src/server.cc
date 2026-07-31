#include <fmt/format.h>
#include <thread>
#include <zmq.hpp>

int main() {
  zmq::context_t ctx;

  zmq::socket_t socket(ctx, zmq::socket_type::rep);
  const std::string endpoint = "ipc:///tmp/server.ipc";
  socket.bind(endpoint);

  fmt::print("Server listening on {}\n", endpoint);

  while (true) {
    zmq::message_t request;
    zmq::recv_result_t res = socket.recv(request, zmq::recv_flags::none);
    if (!res) {
      continue;
    }
    std::string req_str{static_cast<char *>(request.data()), request.size()};
    fmt::print("Received request: {}\n", req_str);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    socket.send(zmq::str_buffer("Hello"), zmq::send_flags::none);
  }

  return 0;
}