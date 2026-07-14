#include "ext.h"

#include "airfx.hpp"
#include "consoles/pdchannel.hpp"

using TWrapped = airwindohhs::pdchannel::PDChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pdchannel~", airwindohhs::pdchannel::k_long_description.data());
}
