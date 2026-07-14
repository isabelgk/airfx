#include "ext.h"

#include "airfx.hpp"
#include "brightness/acceleration2.hpp"

using TWrapped = airwindohhs::acceleration2::Acceleration2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.acceleration2~", airwindohhs::acceleration2::k_long_description.data());
}
