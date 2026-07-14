#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8subout.hpp"

using TWrapped = airwindohhs::console8subout::Console8SubOut<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8subout~", airwindohhs::console8subout::k_long_description.data());
}
