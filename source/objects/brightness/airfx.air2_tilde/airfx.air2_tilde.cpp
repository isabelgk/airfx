#include "ext.h"

#include "airfx.hpp"
#include "brightness/air2.hpp"

using TWrapped = airwindohhs::air2::Air2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.air2~", airwindohhs::air2::k_long_description.data());
}
