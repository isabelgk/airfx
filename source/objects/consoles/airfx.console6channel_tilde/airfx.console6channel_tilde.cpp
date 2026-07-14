#include "ext.h"

#include "airfx.hpp"
#include "consoles/console6channel.hpp"

using TWrapped = airwindohhs::console6channel::Console6Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console6channel~", airwindohhs::console6channel::k_long_description.data());
}
