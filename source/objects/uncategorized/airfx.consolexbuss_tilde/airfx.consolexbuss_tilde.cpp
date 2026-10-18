#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolexbuss.hpp"

using TWrapped = airwindohhs::consolexbuss::ConsoleXBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolexbuss~", airwindohhs::consolexbuss::k_long_description.data());
}
