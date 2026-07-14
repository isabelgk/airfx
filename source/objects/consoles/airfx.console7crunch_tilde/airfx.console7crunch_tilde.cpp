#include "ext.h"

#include "airfx.hpp"
#include "consoles/console7crunch.hpp"

using TWrapped = airwindohhs::console7crunch::Console7Crunch<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console7crunch~", airwindohhs::console7crunch::k_long_description.data());
}
