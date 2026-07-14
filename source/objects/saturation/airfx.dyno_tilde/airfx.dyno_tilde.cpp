#include "ext.h"

#include "airfx.hpp"
#include "saturation/dyno.hpp"

using TWrapped = airwindohhs::dyno::Dyno<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dyno~", airwindohhs::dyno::k_long_description.data());
}
