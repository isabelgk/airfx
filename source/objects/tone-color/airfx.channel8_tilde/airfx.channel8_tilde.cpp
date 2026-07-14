#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channel8.hpp"

using TWrapped = airwindohhs::channel8::Channel8<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channel8~", airwindohhs::channel8::k_long_description.data());
}
