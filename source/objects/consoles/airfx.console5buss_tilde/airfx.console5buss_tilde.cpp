#include "ext.h"

#include "airfx.hpp"
#include "consoles/console5buss.hpp"

using TWrapped = airwindohhs::console5buss::Console5Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console5buss~", airwindohhs::console5buss::k_long_description.data());
}
