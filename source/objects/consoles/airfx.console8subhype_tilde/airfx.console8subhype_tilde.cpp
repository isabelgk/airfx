#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8subhype.hpp"

using TWrapped = airwindohhs::console8subhype::Console8SubHype<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8subhype~", airwindohhs::console8subhype::k_long_description.data());
}
