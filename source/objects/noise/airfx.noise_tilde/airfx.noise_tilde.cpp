#include "ext.h"

#include "airfx.hpp"
#include "noise/noise.hpp"

using TWrapped = airwindohhs::noise::Noise<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.noise~", airwindohhs::noise::k_long_description.data());
}
