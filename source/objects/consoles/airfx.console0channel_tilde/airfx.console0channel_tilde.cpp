#include "ext.h"

#include "airfx.hpp"
#include "consoles/console0channel.hpp"

using TWrapped = airwindohhs::console0channel::Console0Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console0channel~", airwindohhs::console0channel::k_long_description.data());
}
