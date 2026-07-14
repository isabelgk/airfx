#include "ext.h"

#include "airfx.hpp"
#include "consoles/console6buss.hpp"

using TWrapped = airwindohhs::console6buss::Console6Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console6buss~", airwindohhs::console6buss::k_long_description.data());
}
