#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/chimeydeluxe.hpp"

using TWrapped = airwindohhs::chimeydeluxe::ChimeyDeluxe<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chimeydeluxe~", airwindohhs::chimeydeluxe::k_long_description.data());
}
