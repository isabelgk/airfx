#include "ext.h"

#include "airfx.hpp"
#include "saturation/tube2.hpp"

using TWrapped = airwindohhs::tube2::Tube2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tube2~", airwindohhs::tube2::k_long_description.data());
}
