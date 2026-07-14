#include "ext.h"

#include "airfx.hpp"
#include "consoles/atmospherechannel.hpp"

using TWrapped = airwindohhs::atmospherechannel::AtmosphereChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.atmospherechannel~", airwindohhs::atmospherechannel::k_long_description.data());
}
