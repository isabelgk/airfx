#include "ext.h"

#include "airfx.hpp"
#include "consoles/purestconsole3buss.hpp"

using TWrapped = airwindohhs::purestconsole3buss::PurestConsole3Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsole3buss~", airwindohhs::purestconsole3buss::k_long_description.data());
}
