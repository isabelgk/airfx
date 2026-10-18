#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolex2pre.hpp"

using TWrapped = airwindohhs::consolex2pre::ConsoleX2Pre<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolex2pre~", airwindohhs::consolex2pre::k_long_description.data());
}
