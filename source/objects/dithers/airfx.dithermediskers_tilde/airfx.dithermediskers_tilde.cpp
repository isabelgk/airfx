#include "ext.h"

#include "airfx.hpp"
#include "dithers/dithermediskers.hpp"

using TWrapped = airwindohhs::dithermediskers::DitherMeDiskers<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dithermediskers~", airwindohhs::dithermediskers::k_long_description.data());
}
