#include "ext.h"

#include "airfx.hpp"
#include "consoles/purestconsole2buss.hpp"

using TWrapped = airwindohhs::purestconsole2buss::PurestConsole2Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsole2buss~", airwindohhs::purestconsole2buss::k_long_description.data());
}
