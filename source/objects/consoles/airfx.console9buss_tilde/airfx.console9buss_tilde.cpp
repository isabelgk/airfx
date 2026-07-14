#include "ext.h"

#include "airfx.hpp"
#include "consoles/console9buss.hpp"

using TWrapped = airwindohhs::console9buss::Console9Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console9buss~", airwindohhs::console9buss::k_long_description.data());
}
