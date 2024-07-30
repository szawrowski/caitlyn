#include "Caitlyn/__Testing/Macro.h"

using namespace Caitlyn::Test;

int main()
{
    return TestRegistry::Instance().RunAll();
}
