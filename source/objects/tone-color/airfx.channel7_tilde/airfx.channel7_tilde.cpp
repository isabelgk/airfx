#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channel7.hpp"

using TWrapped = airwindohhs::channel7::Channel7<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channel7~", airwindohhs::channel7::k_long_description.data());
}
