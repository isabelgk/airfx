#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8bussout.hpp"

using TWrapped = airwindohhs::console8bussout::Console8BussOut<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8bussout~", airwindohhs::console8bussout::k_long_description.data());
}
