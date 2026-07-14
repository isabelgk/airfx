#include "ext.h"

#include "airfx.hpp"
#include "consoles/c5rawbuss.hpp"

using TWrapped = airwindohhs::c5rawbuss::C5RawBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.c5rawbuss~", airwindohhs::c5rawbuss::k_long_description.data());
}
