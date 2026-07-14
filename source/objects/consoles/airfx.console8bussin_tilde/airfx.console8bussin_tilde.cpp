#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8bussin.hpp"

using TWrapped = airwindohhs::console8bussin::Console8BussIn<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8bussin~", airwindohhs::console8bussin::k_long_description.data());
}
