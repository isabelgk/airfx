#include "ext.h"

#include "airfx.hpp"
#include "consoles/console7channel.hpp"

using TWrapped = airwindohhs::console7channel::Console7Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console7channel~", airwindohhs::console7channel::k_long_description.data());
}
