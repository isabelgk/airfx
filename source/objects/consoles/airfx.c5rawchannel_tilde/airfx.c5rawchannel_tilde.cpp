#include "ext.h"

#include "airfx.hpp"
#include "consoles/c5rawchannel.hpp"

using TWrapped = airwindohhs::c5rawchannel::C5RawChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.c5rawchannel~", airwindohhs::c5rawchannel::k_long_description.data());
}
