#include "ext.h"

#include "airfx.hpp"
#include "consoles/console4channel.hpp"

using TWrapped = airwindohhs::console4channel::Console4Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console4channel~", airwindohhs::console4channel::k_long_description.data());
}
