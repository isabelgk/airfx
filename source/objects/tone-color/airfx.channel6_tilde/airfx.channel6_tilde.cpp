#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channel6.hpp"

using TWrapped = airwindohhs::channel6::Channel6<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channel6~", airwindohhs::channel6::k_long_description.data());
}
