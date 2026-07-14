#include "ext.h"

#include "airfx.hpp"
#include "consoles/purestconsole2channel.hpp"

using TWrapped = airwindohhs::purestconsole2channel::PurestConsole2Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsole2channel~", airwindohhs::purestconsole2channel::k_long_description.data());
}
