#include <print>
#include <sandbox/hello.hpp>

namespace sandbox {
  void hello() { std::print("Hello, {}\n", "World!"); }
}  // namespace sandbox
