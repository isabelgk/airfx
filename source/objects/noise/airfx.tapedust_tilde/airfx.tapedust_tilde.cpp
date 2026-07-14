#include "ext.h"

#include "airfx.hpp"
#include "noise/tapedust.hpp"

using TWrapped = airwindohhs::tapedust::TapeDust<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapedust~", airwindohhs::tapedust::k_long_description.data());
}
