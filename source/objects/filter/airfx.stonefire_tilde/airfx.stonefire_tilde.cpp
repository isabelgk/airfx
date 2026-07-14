#include "ext.h"

#include "airfx.hpp"
#include "filter/stonefire.hpp"

using TWrapped = airwindohhs::stonefire::Stonefire<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.stonefire~", airwindohhs::stonefire::k_long_description.data());
}
