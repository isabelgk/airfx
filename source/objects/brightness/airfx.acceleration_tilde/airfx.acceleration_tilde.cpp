#include "ext.h"

#include "airfx.hpp"
#include "brightness/acceleration.hpp"

using TWrapped = airwindohhs::acceleration::Acceleration<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.acceleration~", airwindohhs::acceleration::k_long_description.data());
}
