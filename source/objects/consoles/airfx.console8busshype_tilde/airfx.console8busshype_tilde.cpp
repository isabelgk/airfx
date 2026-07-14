#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8busshype.hpp"

using TWrapped = airwindohhs::console8busshype::Console8BussHype<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8busshype~", airwindohhs::console8busshype::k_long_description.data());
}
