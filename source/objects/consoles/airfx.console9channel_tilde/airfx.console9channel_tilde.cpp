#include "ext.h"

#include "airfx.hpp"
#include "consoles/console9channel.hpp"

using TWrapped = airwindohhs::console9channel::Console9Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console9channel~", airwindohhs::console9channel::k_long_description.data());
}
