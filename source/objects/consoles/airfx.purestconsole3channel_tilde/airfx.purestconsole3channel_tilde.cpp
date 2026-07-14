#include "ext.h"

#include "airfx.hpp"
#include "consoles/purestconsole3channel.hpp"

using TWrapped = airwindohhs::purestconsole3channel::PurestConsole3Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsole3channel~", airwindohhs::purestconsole3channel::k_long_description.data());
}
