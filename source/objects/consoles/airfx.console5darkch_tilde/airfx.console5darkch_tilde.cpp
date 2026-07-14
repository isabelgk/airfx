#include "ext.h"

#include "airfx.hpp"
#include "consoles/console5darkch.hpp"

using TWrapped = airwindohhs::console5darkch::Console5DarkCh<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console5darkch~", airwindohhs::console5darkch::k_long_description.data());
}
