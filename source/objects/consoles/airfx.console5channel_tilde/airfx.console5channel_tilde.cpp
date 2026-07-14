#include "ext.h"

#include "airfx.hpp"
#include "consoles/console5channel.hpp"

using TWrapped = airwindohhs::console5channel::Console5Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console5channel~", airwindohhs::console5channel::k_long_description.data());
}
