#include <fmt/base.h>
#include <fmt/core.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include <oneapi/tbb/blocked_range.h>
#include <oneapi/tbb/parallel_for.h>
#include <tbb/parallel_for.h>

#include "clang/Frontend/CompilerInstance.h"
#include <clang/Frontend/ASTUnit.h>

#include <zmq.hpp>

#include <toml.hpp>

template <typename T>
concept IsSmall = sizeof(T) <= sizeof(int);

int main() {
  fmt::print("Hello vcpkg\n");
  FMT_VERSION;

  llvm::InitializeNativeTarget();

  tbb::parallel_for(tbb::blocked_range(0, 10), [](const auto &range) {
    for (auto i = range.begin(); i != range.end(); ++i) {
      fmt::print("tbb: {}\n", i);
    }
  });

  clang::CompilerInstance Clang;

  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::push);
  sock.bind("inproc://test");
  sock.send(zmq::str_buffer("Hello World"), zmq::send_flags::dontwait);
  return 0;
}