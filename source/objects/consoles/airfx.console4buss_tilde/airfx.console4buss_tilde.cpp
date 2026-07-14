#include "ext.h"

#include "airfx.hpp"
#include "consoles/console4buss.hpp"

using TWrapped = airwindohhs::console4buss::Console4Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console4buss~", airwindohhs::console4buss::k_long_description.data());
}
