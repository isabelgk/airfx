#include "ext.h"

#include "airfx.hpp"
#include "consoles/consolemcchannel.hpp"

using TWrapped = airwindohhs::consolemcchannel::ConsoleMCChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolemcchannel~", airwindohhs::consolemcchannel::k_long_description.data());
}
