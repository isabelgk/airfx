#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channel4.hpp"

using TWrapped = airwindohhs::channel4::Channel4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channel4~", airwindohhs::channel4::k_long_description.data());
}
