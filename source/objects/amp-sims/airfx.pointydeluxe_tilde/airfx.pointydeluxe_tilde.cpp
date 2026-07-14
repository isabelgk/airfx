#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/pointydeluxe.hpp"

using TWrapped = airwindohhs::pointydeluxe::PointyDeluxe<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pointydeluxe~", airwindohhs::pointydeluxe::k_long_description.data());
}
