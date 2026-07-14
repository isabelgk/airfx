#include "ext.h"

#include "airfx.hpp"
#include "noise/denoise.hpp"

using TWrapped = airwindohhs::denoise::DeNoise<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.denoise~", airwindohhs::denoise::k_long_description.data());
}
