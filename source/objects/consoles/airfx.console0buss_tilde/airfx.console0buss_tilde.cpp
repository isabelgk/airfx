#include "ext.h"

#include "airfx.hpp"
#include "consoles/console0buss.hpp"

using TWrapped = airwindohhs::console0buss::Console0Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console0buss~", airwindohhs::console0buss::k_long_description.data());
}
