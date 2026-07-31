#pragma once

#include <string>

#include <msgpack.hpp>

#include <fmt/format.h>

struct MyData {
  std::string name;
  int age;

  MSGPACK_DEFINE(name, age);
};

inline std::string format_as(const MyData &data) {
  return fmt::format("MyData(name={}, age={})", data.name, data.age);
}