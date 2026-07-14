#include "ext.h"

#include "airfx.hpp"
#include "consoles/console7buss.hpp"

using TWrapped = airwindohhs::console7buss::Console7Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console7buss~", airwindohhs::console7buss::k_long_description.data());
}
