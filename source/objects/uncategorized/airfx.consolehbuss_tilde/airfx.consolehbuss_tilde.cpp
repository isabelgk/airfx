#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolehbuss.hpp"

using TWrapped = airwindohhs::consolehbuss::ConsoleHBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolehbuss~", airwindohhs::consolehbuss::k_long_description.data());
}
