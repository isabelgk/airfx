#include "ext.h"

#include "airfx.hpp"
#include "consoles/console7cascade.hpp"

using TWrapped = airwindohhs::console7cascade::Console7Cascade<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console7cascade~", airwindohhs::console7cascade::k_long_description.data());
}
