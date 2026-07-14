#include "ext.h"

#include "airfx.hpp"
#include "consoles/everyconsole.hpp"

using TWrapped = airwindohhs::everyconsole::EveryConsole<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.everyconsole~", airwindohhs::everyconsole::k_long_description.data());
}
