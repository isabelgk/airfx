#include "ext.h"

#include "airfx.hpp"
#include "noise/darknoise.hpp"

using TWrapped = airwindohhs::darknoise::DarkNoise<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.darknoise~", airwindohhs::darknoise::k_long_description.data());
}
