#include <caitlyn/test.h>

int main() {
  cait::test::registry_t::instance().run_all();
  return 0;
}