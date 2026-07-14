#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channel5.hpp"

using TWrapped = airwindohhs::channel5::Channel5<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channel5~", airwindohhs::channel5::k_long_description.data());
}
