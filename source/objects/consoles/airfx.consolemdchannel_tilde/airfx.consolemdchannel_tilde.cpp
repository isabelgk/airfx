#include "ext.h"

#include "airfx.hpp"
#include "consoles/consolemdchannel.hpp"

using TWrapped = airwindohhs::consolemdchannel::ConsoleMDChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolemdchannel~", airwindohhs::consolemdchannel::k_long_description.data());
}
