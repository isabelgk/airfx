#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/purestconsole4channel.hpp"

using TWrapped = airwindohhs::purestconsole4channel::PurestConsole4Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsole4channel~", airwindohhs::purestconsole4channel::k_long_description.data());
}
