#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/purestconsole4buss.hpp"

using TWrapped = airwindohhs::purestconsole4buss::PurestConsole4Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsole4buss~", airwindohhs::purestconsole4buss::k_long_description.data());
}
