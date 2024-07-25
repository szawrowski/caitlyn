#include "caitlyn/__testing/macro.h"

int main()
{
    return cait::test::registry_t::instance().run_all();
}
