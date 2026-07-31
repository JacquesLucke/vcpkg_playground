#include <fmt/format.h>
#include <zmq.hpp>
#include <zmq_addon.hpp>

using namespace std::string_view_literals;

int main() {
  zmq::context_t ctx;

  zmq::socket_t socket(ctx, zmq::socket_type::router);
  const std::string endpoint = "ipc:///tmp/server.ipc";
  socket.bind(endpoint);

  fmt::print("Server listening on {}\n", endpoint);

  while (true) {
    std::vector<zmq::message_t> recv_parts;
    auto result = zmq::recv_multipart(socket, std::back_inserter(recv_parts));
    if (!result) {
      continue;
    }
    fmt::print("Received {} parts\n", recv_parts.size());
    if (recv_parts.size() != 3) {
      continue;
    }
    const std::string_view client_id = recv_parts[0].to_string_view();
    const std::string_view req_message = recv_parts[2].to_string_view();

    fmt::print("Received request from {}: {}\n", client_id, req_message);

    std::vector<zmq::message_t> reply_parts;
    reply_parts.push_back(std::move(recv_parts[0]));
    reply_parts.push_back(std::move(recv_parts[1]));
    reply_parts.push_back(zmq::message_t{fmt::format("Hello {}", req_message)});
    zmq::send_multipart(socket, std::move(reply_parts));
  }

  return 0;
}