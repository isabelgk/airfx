#include "ext.h"

#include "airfx.hpp"
#include "brightness/air.hpp"

using TWrapped = airwindohhs::air::Air<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.air~", airwindohhs::air::k_long_description.data());
}
