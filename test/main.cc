#include <caitlyn/test.h>

int main() {
  return cait::test::registry_t::instance().run_all();
}